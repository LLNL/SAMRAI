/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and LICENSE.
 *
 * Copyright:     (c) 1997-2023 Lawrence Livermore National Security, LLC
 * Description:   Staged peer-to-peer communication.
 *
 ************************************************************************/
#ifndef included_tbox_AsyncCommPeer_C
#define included_tbox_AsyncCommPeer_C

#include "SAMRAI/tbox/AsyncCommPeer.h"

#include "SAMRAI/tbox/PIO.h"
#include "SAMRAI/tbox/SAMRAIManager.h"
#include "SAMRAI/tbox/StartupShutdownManager.h"
#include "SAMRAI/tbox/Timer.h"
#include "SAMRAI/tbox/TimerManager.h"


#ifdef HAVE_UMPIRE
#include "umpire/strategy/QuickPool.hpp"
#include "umpire/ResourceManager.hpp"
#endif

#include <cstring>

#if !defined(__BGL_FAMILY__) && defined(__xlC__)
/*
 * Suppress XLC warnings
 */
#pragma report(disable, CPPC5334)
#pragma report(disable, CPPC5328)
#endif

namespace SAMRAI {
namespace tbox {

/*
 * This class uses a non-deterministic algorithm, which can be
 * very hard to debug.  To help debugging, we keep some special
 * debugging code that is activated when AsyncCommPeer_DEBUG_OUTPUT
 * is defined.
 */
// #define AsyncCommPeer_DEBUG_OUTPUT

template<class TYPE>
std::shared_ptr<Timer> AsyncCommPeer<TYPE>::t_default_send_timer;
template<class TYPE>
std::shared_ptr<Timer> AsyncCommPeer<TYPE>::t_default_recv_timer;
template<class TYPE>
std::shared_ptr<Timer> AsyncCommPeer<TYPE>::t_default_wait_timer;

template<class TYPE>
StartupShutdownManager::Handler
AsyncCommPeer<TYPE>::s_initialize_finalize_handler(
   AsyncCommPeer<TYPE>::initializeCallback,
   0,
   0,
   AsyncCommPeer<TYPE>::finalizeCallback,
   StartupShutdownManager::priorityTimers);

/*
 ***********************************************************************
 ***********************************************************************
 */
template<class TYPE>
AsyncCommPeer<TYPE>::AsyncCommPeer():
   AsyncCommStage::Member(),
   d_peer_rank(-1),
   d_base_op(undefined),
   d_next_task_op(none),
   d_max_first_data_len(1),
   d_full_count(0),
   d_external_buf(0),
   d_internal_buf_size(0),
   d_internal_buf(0),
   d_count_buf(0),
   d_mpi(SAMRAI_MPI::getSAMRAIWorld()),
   d_tag0(-1),
   d_tag1(-1),
#ifdef HAVE_UMPIRE
   d_allocator(umpire::ResourceManager::getInstance().getAllocator(umpire::resource::Host)),
#endif
   t_send_timer(t_default_send_timer),
   t_recv_timer(t_default_recv_timer),
   t_wait_timer(t_default_wait_timer)
{
   d_report_send_completion[0] = d_report_send_completion[1] = false;
   if (!t_default_wait_timer) {
      /*
       * This should not be needed, but somehow initializeCallback()
       * may not have called yet.
       */
      initializeCallback();
      t_send_timer = t_default_send_timer;
      t_recv_timer = t_default_recv_timer;
      t_wait_timer = t_default_wait_timer;
   }
}

/*
 ***********************************************************************
 * Construct a simple object that works with a communication stage.
 * All parameters are set to reasonable defaults or, if appropriate,
 * invalid values.
 ***********************************************************************
 */
template<class TYPE>
AsyncCommPeer<TYPE>::AsyncCommPeer(
   AsyncCommStage* stage,
   AsyncCommStage::Handler* handler):
   AsyncCommStage::Member(2, stage, handler),
   d_peer_rank(-1),
   d_base_op(undefined),
   d_next_task_op(none),
   d_max_first_data_len(1),
   d_full_count(0),
   d_external_buf(0),
   d_internal_buf_size(0),
   d_internal_buf(0),
   d_count_buf(0),
   d_mpi(SAMRAI_MPI::getSAMRAIWorld()),
   d_tag0(-1),
   d_tag1(-1),
#ifdef HAVE_UMPIRE
   d_allocator(umpire::ResourceManager::getInstance().getAllocator(umpire::resource::Host)),
#endif
   t_send_timer(t_default_send_timer),
   t_recv_timer(t_default_recv_timer),
   t_wait_timer(t_default_wait_timer)
{
   d_report_send_completion[0] = d_report_send_completion[1] = false;
   if (!t_default_wait_timer) {
      /*
       * This should not be needed, but somehow initializeCallback()
       * may not have called yet.
       */
      initializeCallback();
      t_send_timer = t_default_send_timer;
      t_recv_timer = t_default_recv_timer;
      t_wait_timer = t_default_wait_timer;
   }
}

/*
 ***********************************************************************
 ***********************************************************************
 */
template<class TYPE>
AsyncCommPeer<TYPE>::~AsyncCommPeer()
{
   if (!isDone()) {
      TBOX_ERROR("Deallocating an AsyncCommPeer object while communication\n"
         << "is pending leads to lost messages.\n"
         << "mpi_communicator = " << d_mpi.getCommunicator()
         << ",  mpi_tag = " << d_tag0 << ", " << d_tag1);
   }

   if (d_internal_buf) {
#ifdef HAVE_UMPIRE
      d_allocator.deallocate(
         (char*)d_internal_buf, d_internal_buf_size * sizeof(FlexData));
#else
      free(d_internal_buf);
#endif
      d_internal_buf = 0;
   }
   if (d_count_buf) {
#ifdef HAVE_UMPIRE
      d_allocator.deallocate(
         (char*)d_count_buf, 2 * sizeof(FlexData));
#else
      free(d_count_buf);
#endif
      d_count_buf = 0;
   }
   d_first_recv_buf = 0;

}

/*
 ***********************************************************************
 * Initialize data as if constructed with the given arguments.
 ***********************************************************************
 */
template<class TYPE>
void
AsyncCommPeer<TYPE>::initialize(
   AsyncCommStage* stage,
   AsyncCommStage::Handler* handler)
{
   if (!isDone()) {
      TBOX_ERROR("It is illegal to re-initialize a AsyncCommPeer\n"
         << "while it has current messages.\n");
   }
   attachStage(2, stage);
   setHandler(handler);
   d_base_op = undefined;
   d_next_task_op = none;
}

/*
 *********************************************************************
 * Check whether the current (or last) operation has completed.
 *********************************************************************
 */
template<class TYPE>
bool
AsyncCommPeer<TYPE>::proceedToNextWait()
{
   switch (d_base_op) {
      case send: return checkSend();

      case recv: return checkRecv();

      case undefined:
         TBOX_ERROR("There is no current operation to check.\n"
         << "mpi_communicator = " << d_mpi.getCommunicator()
         << ",  mpi_tag = " << d_tag0 << ", " << d_tag1);
         break;
      default:
         TBOX_ERROR("Library error: attempt to use an operation that\n"
         << "has not been written yet.\n"
         << "mpi_communicator = " << d_mpi.getCommunicator()
         << ",  mpi_tag = " << d_tag0 << ", " << d_tag1);
   }
   return true;
}

/*
 *********************************************************************
 * Wait for current communication operation to complete.
 *
 * Wait for all requests to come in and call proceedToNextWait().
 * Repeat until all tasks of the entire communication operation is
 * complete.
 *********************************************************************
 */
template<class TYPE>
void
AsyncCommPeer<TYPE>::completeCurrentOperation()
{
   SAMRAI_MPI::Request * const req = getRequestPointer();
   SAMRAI_MPI::Status* mpi_status = getStatusPointer();

   while (!isDone()) {

      t_wait_timer->start();
      int errf = SAMRAI_MPI::Waitall(2,
            req,
            mpi_status);
      t_wait_timer->stop();

      if (errf != MPI_SUCCESS) {
         TBOX_ERROR("Error in MPI_wait call.\n"
            << "mpi_communicator = " << d_mpi.getCommunicator()
            << ",  mpi_tag = " << d_tag0);
      }

      proceedToNextWait();

   }
}

/*
 ************************************************************************
 * Set internal parameters for performing the send
 * and call checkSend to perform the communication.
 ************************************************************************
 */
template<class TYPE>
bool
AsyncCommPeer<TYPE>::beginSend(
   const TYPE* buffer,
   int size,
   bool automatic_push_to_completion_queue)
{
   if (getNextTaskOp() != none) {
      TBOX_ERROR("Cannot begin communication while another is in progress.\n"
         << "mpi_communicator = " << d_mpi.getCommunicator()
         << ",  mpi_tag = " << d_tag0);
   }
#ifdef DEBUG_CHECK_ASSERTIONS
   checkMPIParams();
#endif
   d_external_buf = buffer;
   d_full_count = size;
   d_base_op = send;
   d_next_task_op = send_start;
   bool status = checkSend(automatic_push_to_completion_queue);
   d_external_buf = 0;
   return status;
}

template<class TYPE>
void
AsyncCommPeer<TYPE>::resizeBuffer(
   size_t size)
{
   TBOX_ASSERT(!hasPendingRequests());

   if (d_internal_buf_size < size) {
      if (d_internal_buf) {
#ifdef HAVE_UMPIRE
         d_internal_buf =
            (FlexData *)umpire::ResourceManager::getInstance().reallocate(
               d_internal_buf, size * sizeof(FlexData));
#else
         d_internal_buf =
            (FlexData *)realloc(d_internal_buf, size * sizeof(FlexData));
#endif
      } else {
#ifdef HAVE_UMPIRE
         d_internal_buf =
            (FlexData *)d_allocator.allocate(size * sizeof(FlexData));
#else
         d_internal_buf = (FlexData *)malloc(size * sizeof(FlexData));
#endif
      }
      d_internal_buf_size = size;
   }
}

/*
 ************************************************************************
 * Check and advance a send operation.  The exact actions depend on where
 * in the send operation we are.
 *
 * This method is written to exit early if progress is blocked by
 * communication waits.  It uses d_next_task_op to mark its progress and
 * return there when called again.  The big switch statement jumps to the
 * place where it needs to continue.
 ************************************************************************
 */
template<class TYPE>
bool
AsyncCommPeer<TYPE>::checkSend(
   bool automatic_push_to_completion_queue)
{
   if (getBaseOp() != send) {
      TBOX_ERROR("Cannot check nonexistent send operation.\n"
         << "mpi_communicator = " << d_mpi.getCommunicator()
         << ",  mpi_tag = " << d_tag0 << ", " << d_tag1);
   }
   SAMRAI_MPI::Request * const req = getRequestPointer();
   int flag = 0;

   if (d_next_task_op != none) {

      if (d_next_task_op == send_start) {

         if (d_max_first_data_len >= d_full_count) {
            /*
             * Data fits within the limit of the first message, so
             * send it all in a single chunk.  Append integers to the
             * data indicating this is the first message and the size
             * of the message.
             */

            const size_t first_chunk_count = getNumberOfFlexData(d_full_count);
            resizeBuffer(first_chunk_count + 2);
            std::memcpy(static_cast<void*>(d_internal_buf),
               static_cast<const void*>(d_external_buf),
               d_full_count * sizeof(TYPE));
            d_internal_buf[first_chunk_count].d_i = 0; // Indicates first message.
            d_internal_buf[first_chunk_count + 1].d_i =
               static_cast<int>(d_full_count); // True data count.

            TBOX_ASSERT(req[0] == MPI_REQUEST_NULL);
            req[0] = MPI_REQUEST_NULL;
            t_send_timer->start();

            d_mpi_err = d_mpi.Isend(d_internal_buf,
                  static_cast<int>(sizeof(FlexData) * (first_chunk_count + 2)),
                  MPI_BYTE,
                  d_peer_rank,
                  d_tag0,
                  &req[0]);
            t_send_timer->stop();
            if (d_mpi_err != MPI_SUCCESS) {
               TBOX_ERROR("Error in MPI_Isend.\n"
                  << "mpi_communicator = " << d_mpi.getCommunicator()
                  << ",  mpi_tag = " << d_tag0);
            }
#ifdef AsyncCommPeer_DEBUG_OUTPUT
            d_report_send_completion[0] = true;
            plog << "tag0-" << d_tag0
                 << " sending " << d_full_count << " TYPEs + 2 int as "
                 << sizeof(FlexData) * (d_full_count + 2)
                 << " bytes to " << d_peer_rank << " in checkSend"
                 << std::endl;
#endif
         } else {
            /*
             * Send oversized data in two chunks.  The first chunk contains the
             * first d_max_first_data_len items.  The second contains the rest.
             * Each chunk is appended with a sequence number and the true size of
             * the data the user wants to send.
             *
             * Note that we allocate d_internal_buf to hold each chunk with its
             * overhead data.  Thus, the two chunks will not be contiguous in
             * d_internal_buf.
             */

            const size_t first_chunk_count = getNumberOfFlexData(
                  d_max_first_data_len);
            const size_t second_chunk_count = getNumberOfFlexData(
                  d_full_count - d_max_first_data_len);

            resizeBuffer(first_chunk_count + 2 + second_chunk_count + 2);

            // Stuff and send first message.
            std::memcpy(static_cast<void*>(d_internal_buf),
               static_cast<const void*>(d_external_buf),
               d_max_first_data_len * (sizeof(TYPE)));
            d_internal_buf[first_chunk_count].d_i = 0;
            d_internal_buf[first_chunk_count + 1].d_i =
               static_cast<int>(d_full_count);
            TBOX_ASSERT(req[0] == MPI_REQUEST_NULL);
#ifdef DEBUG_CHECK_ASSERTIONS
            req[0] = MPI_REQUEST_NULL;
#endif
            t_send_timer->start();
            d_mpi_err = d_mpi.Isend(
                  d_internal_buf,
                  static_cast<int>(sizeof(FlexData) * (first_chunk_count + 2)),
                  MPI_BYTE,
                  d_peer_rank,
                  d_tag0,
                  &req[0]);
            t_send_timer->stop();
            if (d_mpi_err != MPI_SUCCESS) {
               TBOX_ERROR("Error in MPI_Isend.\n"
                  << "mpi_communicator = " << d_mpi.getCommunicator()
                  << ",  mpi_tag = " << d_tag0);
            }

            // Stuff and send second message.
            std::memcpy(static_cast<void*>(&d_internal_buf[first_chunk_count + 2]),
               static_cast<const void*>(d_external_buf + d_max_first_data_len),
               (d_full_count - d_max_first_data_len) * (sizeof(TYPE)));
            d_internal_buf[first_chunk_count + second_chunk_count + 2].d_i = 1;
            d_internal_buf[first_chunk_count + second_chunk_count
                           + 3].d_i = static_cast<int>(d_full_count);
            TBOX_ASSERT(req[1] == MPI_REQUEST_NULL);
#ifdef DEBUG_CHECK_ASSERTIONS
            req[1] = MPI_REQUEST_NULL;
#endif
            t_send_timer->start();
            d_mpi_err = d_mpi.Isend(
                  &d_internal_buf[first_chunk_count + 2],
                  static_cast<int>(sizeof(FlexData) * (second_chunk_count + 2)),
                  MPI_BYTE,
                  d_peer_rank,
                  d_tag1,
                  &req[1]);
            t_send_timer->stop();
#ifdef AsyncCommPeer_DEBUG_OUTPUT
            d_report_send_completion[1] = true;
            plog << "tag1-" << d_tag1
                 << " sending " << d_full_count << " TYPEs + 4 int as "
                 << sizeof(FlexData) * (first_chunk_count + 2) << " and "
                 << sizeof(FlexData) * (second_chunk_count + 2)
                 << " byte chunks to " << d_peer_rank << " in checkSend"
                 << std::endl;
#endif
         }
      }
      if (d_next_task_op == send_start || d_next_task_op == send_check) {
         // Determine if send completed.
         for (int ic = 0; ic < 2; ++ic) {
            if (req[ic] != MPI_REQUEST_NULL) {
               SAMRAI_MPI::Status* mpi_status = getStatusPointer();
               resetStatus(mpi_status[ic]);
               d_mpi_err = SAMRAI_MPI::Test(&req[ic], &flag, &mpi_status[ic]);
               if (d_mpi_err != MPI_SUCCESS) {
                  TBOX_ERROR("Error in MPI_Test.\n"
                     << "Error-in-status is "
                     << (d_mpi_err == MPI_ERR_IN_STATUS) << '\n'
                     << "MPI_ERROR value is " << mpi_status[ic].MPI_ERROR
                     << '\n'
                     << "mpi_communicator = " << d_mpi.getCommunicator()
                     << ",  mpi_tag = " << d_tag0);
               }
            }
            if (req[ic] == MPI_REQUEST_NULL && d_report_send_completion[ic]) {
#ifdef AsyncCommPeer_DEBUG_OUTPUT
               plog << "tag" << ic << "-" << (ic == 0 ? d_tag0 : d_tag1)
                    << " sent <N/A> bytes to " << d_peer_rank
                    << " in checkSend"
                    << std::endl;
               d_report_send_completion[ic] = false;
#endif
            }
         }

         if (req[0] != MPI_REQUEST_NULL || req[1] != MPI_REQUEST_NULL) {
            // Sends not completed.  Need to repeat send_check.
            d_next_task_op = send_check;
         } else {
            // Sends completed.  No next task.
            d_next_task_op = none;
            d_external_buf = 0;
            d_full_count = 0;
         }
      }

      if (d_next_task_op != none && d_next_task_op != send_check &&
          d_next_task_op != send_start) { 
         TBOX_ERROR("checkSend is incompatible with current state.\n"
         << "mpi_communicator = " << d_mpi.getCommunicator()
         << ",  mpi_tag = " << d_tag0);
      }
   }

   if (automatic_push_to_completion_queue && d_next_task_op == none) {
      pushToCompletionQueue();
   }

   return d_next_task_op == none;
}

/*
 ************************************************************************
 * Set internal parameters for performing the receive
 * and call checkRecv to perform the communication.
 ************************************************************************
 */
template<class TYPE>
bool
AsyncCommPeer<TYPE>::beginRecv(
   bool automatic_push_to_completion_queue)
{
   if (getNextTaskOp() != none) {
      TBOX_ERROR("Cannot begin communication while another is in progress.\n"
         << "mpi_communicator = " << d_mpi.getCommunicator()
         << ",  mpi_tag = " << d_tag0);
   }
#ifdef DEBUG_CHECK_ASSERTIONS
   checkMPIParams();
#endif
   d_full_count = 0;
   d_base_op = recv;
   d_next_task_op = recv_start;
   return checkRecv(automatic_push_to_completion_queue);
}

/*
 ************************************************************************
 * Check and advance a receive operation.  The exact actions depend on
 * where in the receive operation we are.
 *
 * This method is written to exit early if progress is blocked by
 * communication waits.  It uses d_next_task_op to mark its progress and
 * return there when called again.  The big switch statement jumps to the
 * place where it needs to continue.
 ************************************************************************
 */
template<class TYPE>
bool
AsyncCommPeer<TYPE>::checkRecv(
   bool automatic_push_to_completion_queue)
{
   if (getBaseOp() != recv) {
      TBOX_ERROR("Cannot check nonexistent receive operation.\n"
         << "mpi_communicator = " << d_mpi.getCommunicator()
         << ",  mpi_tag = " << d_tag0 << ", " << d_tag1);
   }
   SAMRAI_MPI::Request * const req = getRequestPointer();
   SAMRAI_MPI::Status * const mpi_status = getStatusPointer();
   int flag = 0;

   if (d_next_task_op != none) {
      bool task_entered = false; 
      if (d_next_task_op == recv_start) {
         task_entered = true;
         d_full_count = 0; // Full count is unknown before receiving first message.

         {
            // Post receive for first (and maybe only) chunk of data.
            const size_t first_chunk_count = getNumberOfFlexData(
                  d_max_first_data_len);

            if (first_chunk_count > 0) {
               resizeBuffer(first_chunk_count + 2);
               d_first_recv_buf = d_internal_buf;
            } else {
               // If the size of the first chunk is zero, due to
               // d_max_first_data_len being set to zero, then we use
               // a small buffer to get only the full count size, deferring
               // the receipt of the full data to the second Irecv.
               if (d_count_buf) {
#ifdef HAVE_UMPIRE
                  d_allocator.deallocate(
                     (char*)d_count_buf, 2 * sizeof(FlexData));
#else
                  free(d_count_buf);
#endif
               }
#ifdef HAVE_UMPIRE
               d_count_buf =
                  (FlexData *)d_allocator.allocate(2 * sizeof(FlexData));
#else
               d_count_buf = (FlexData *)malloc(2 * sizeof(FlexData));
#endif
               d_first_recv_buf = d_count_buf;
            }

            TBOX_ASSERT(req[0] == MPI_REQUEST_NULL);
#ifdef DEBUG_CHECK_ASSERTIONS
            req[0] = MPI_REQUEST_NULL;
#endif
            t_recv_timer->start();
            d_mpi_err = d_mpi.Irecv(
                  d_first_recv_buf,
                  static_cast<int>(sizeof(FlexData) * (first_chunk_count + 2)),
                  MPI_BYTE,
                  d_peer_rank,
                  d_tag0,
                  &req[0]);
            t_recv_timer->stop();
            if (d_mpi_err != MPI_SUCCESS) {
               TBOX_ERROR("Error in MPI_Irecv.\n"
                  << "mpi_communicator = " << d_mpi.getCommunicator()
                  << ",  mpi_tag = " << d_tag0);
            }
#ifdef AsyncCommPeer_DEBUG_OUTPUT
            plog << "tag0-" << d_tag0
                 << " receiving up to " << d_max_first_data_len
                 << " TYPEs and 2 ints as "
                 << sizeof(FlexData) * (first_chunk_count + 2)
                 << " bytes from " << d_peer_rank
                 << " in checkRecv"
                 << std::endl;
#endif
         }
      }

      bool breakout = false;
      if (d_next_task_op == recv_start || d_next_task_op == recv_check0) {
         task_entered = true;
         // Check on first message.

         if (req[0] != MPI_REQUEST_NULL) {
            resetStatus(mpi_status[0]);
            d_mpi_err = SAMRAI_MPI::Test(&req[0], &flag, &mpi_status[0]);
            if (d_mpi_err != MPI_SUCCESS) {
               TBOX_ERROR("Error in MPI_Test.\n"
                  << "Error-in-status is "
                  << (d_mpi_err == MPI_ERR_IN_STATUS) << '\n'
                  << "MPI_ERROR value is " << mpi_status[0].MPI_ERROR
                  << '\n'
                  << "mpi_communicator = " << d_mpi.getCommunicator()
                  << ",  mpi_tag = " << d_tag0);
            }
         }

         if (req[0] != MPI_REQUEST_NULL) {
            // First message not yet received.  Need to recheck later.
            d_next_task_op = recv_check0;
            breakout = true;
         } else {
            // First message is received.
            int icount = -1;
            d_mpi_err = SAMRAI_MPI::Get_count(&mpi_status[0], MPI_BYTE, &icount);
            if (d_mpi_err != MPI_SUCCESS) {
               TBOX_ERROR("Error in MPI_Get_count.\n"
                  << "error flag = " << d_mpi_err);
            }
            const size_t count = icount / sizeof(FlexData); // Convert byte count to item count.
#ifdef DEBUG_CHECK_ASSERTIONS
#ifdef AsyncCommPeer_DEBUG_OUTPUT
            plog << "tag0-" << d_tag0
                 << " received " << count << " FlexData as " << icount
                 << " bytes from " << d_peer_rank << " in checkRecv"
                 << std::endl;
#endif
#endif
            TBOX_ASSERT(count <= d_max_first_data_len + 2);
            TBOX_ASSERT(mpi_status[0].MPI_TAG == d_tag0);
            TBOX_ASSERT(mpi_status[0].MPI_SOURCE == d_peer_rank);
            TBOX_ASSERT(req[0] == MPI_REQUEST_NULL);
            // Get full count embedded in message.
            d_full_count = d_first_recv_buf[count - 1].d_i;

            TBOX_ASSERT(d_first_recv_buf[count - 2].d_i == 0); // Sequence number check.
            TBOX_ASSERT(getNumberOfFlexData(d_full_count) >= count - 2);

            if (d_full_count > d_max_first_data_len) {

               /*
                * There is another data chunk.  Post another receive
                * call, placing it immediately after the data portion
                * of the first chunk so that the user data is
                * contiguous in d_internal_buf.
                */

               const size_t second_chunk_count = getNumberOfFlexData(
                     d_full_count - d_max_first_data_len);

               size_t new_internal_buf_size =
                  d_internal_buf_size + second_chunk_count;

               // If the first Irecv didn't use d_internal_buf, then
               // the message in the second Irecv will contain the entire
               // buffer of data for this communicattion instance, and we need
               // to add 2 to the buffer size to make room for the trailing
               // metadata.
               if (d_internal_buf_size == 0) {
                  new_internal_buf_size += 2;
               }
               resizeBuffer(new_internal_buf_size);

               TBOX_ASSERT(req[1] == MPI_REQUEST_NULL);
               req[1] = MPI_REQUEST_NULL;
               t_recv_timer->start();
               d_mpi_err = d_mpi.Irecv(
                     (TYPE *)(d_internal_buf) + d_max_first_data_len,
                     static_cast<int>(sizeof(FlexData) * (second_chunk_count + 2)),
                     MPI_BYTE,
                     d_peer_rank,
                     d_tag1,
                     &req[1]);
               t_recv_timer->stop();
               if (d_mpi_err != MPI_SUCCESS) {
                  TBOX_ERROR("Error in MPI_Irecv.\n"
                     << "mpi_communicator = " << d_mpi.getCommunicator()
                     << ",  mpi_tag = " << d_tag0);
               }
#ifdef AsyncCommPeer_DEBUG_OUTPUT
               plog << "tag1-" << d_tag1
                    << " receiving " << d_full_count - d_max_first_data_len
                    << " from " << d_peer_rank
                    << " in checkRecv"
                    << std::endl;
#endif
            } else {
               /*
                * There is no follow-up data.  All data are now received.
                * So we don't need to check the second message.
                */
               d_next_task_op = none;
               breakout = true;
            }
         }
      }

      if (!breakout &&
            (d_next_task_op == recv_start || d_next_task_op == recv_check0 ||
             d_next_task_op == recv_check1)) { 

         task_entered = true;
 
         // Check on the second message.

         if (req[1] != MPI_REQUEST_NULL) {
            resetStatus(mpi_status[1]);
            d_mpi_err = SAMRAI_MPI::Test(&req[1], &flag, &mpi_status[1]);
            if (d_mpi_err != MPI_SUCCESS) {
               TBOX_ERROR("Error in MPI_Test.\n"
                  << "Error-in-status is "
                  << (d_mpi_err == MPI_ERR_IN_STATUS) << '\n'
                  << "MPI_ERROR value is " << mpi_status[1].MPI_ERROR
                  << '\n'
                  << "mpi_communicator = " << d_mpi.getCommunicator()
                  << ",  mpi_tag = " << d_tag1);
            }
            if (flag == 1) {
               // Second message received.
               const size_t first_chunk_count = getNumberOfFlexData(
                     d_max_first_data_len);
               const size_t second_chunk_count = getNumberOfFlexData(
                     d_full_count - d_max_first_data_len);
#ifdef DEBUG_CHECK_ASSERTIONS
               int icount = -1;
               SAMRAI_MPI::Get_count(&mpi_status[1], MPI_BYTE, &icount);
               const size_t count = icount / sizeof(FlexData); // Convert byte count to item count.
#ifdef AsyncCommPeer_DEBUG_OUTPUT
               plog << "tag1-" << d_tag1
                    << " received " << count << " FlexType from "
                    << d_peer_rank << " in checkRecv"
                    << std::endl;
#endif
               TBOX_ASSERT(count == second_chunk_count + 2);
               TBOX_ASSERT(mpi_status[1].MPI_TAG == d_tag1);
               TBOX_ASSERT(mpi_status[1].MPI_SOURCE == d_peer_rank);
               TBOX_ASSERT(req[1] == MPI_REQUEST_NULL);
#endif
               /*
                * If sizeof(TYPE) < sizeof(FlexData), there is a
                * potential side effect that the integer overhead info
                * may not have the correct allignment and must be
                * realligned before being readable.
                *
                * I shift_bytes is non-zero, there is an allignment
                * problem wherein the integer overhead data does not
                * start on an integer memory.  The overhead data was
                * correctly alligned on the sending processor, but on
                * the receiver, we put the second message right at the
                * end of the first chunk of data (to make the chunks
                * contiguous), which may shift the integer data away
                * from integer allignment.  The overhead data should
                * be shifted to allign with FlexData before being
                * read.
                */
               const int shift_bytes = static_cast<int>(
                     first_chunk_count * sizeof(FlexData) - d_max_first_data_len
                     * sizeof(TYPE));
               TBOX_ASSERT(shift_bytes >= 0);
               if (shift_bytes > 0) {
                  char* correct_place, * current_place;
                  current_place = (char *)((TYPE *)(d_internal_buf)
                                           + d_max_first_data_len
                                           + second_chunk_count
                                           * sizeof(FlexData));
                  correct_place = current_place + shift_bytes;
                  std::memmove(correct_place, current_place, 2
                     * sizeof(FlexData));
               }
               // Check that this actually is the second message:
               TBOX_ASSERT(d_internal_buf[first_chunk_count
                                          + second_chunk_count].d_i == 1);
               // Check consistency of the claimed full size:
               TBOX_ASSERT(
                  d_internal_buf[first_chunk_count
                                 + second_chunk_count + 1].d_i ==
                  static_cast<int>(d_full_count));
            }
         }
         if (req[1] != MPI_REQUEST_NULL) {
            d_next_task_op = recv_check1;
         } else {
            d_next_task_op = none;
         }
      }

      if (!task_entered) {
         TBOX_ERROR("checkRecv is incompatible with current state.\n"
         << "mpi_communicator = " << d_mpi.getCommunicator()
         << ",  mpi_tag = " << d_tag0);
      }
   }

   if (automatic_push_to_completion_queue && d_next_task_op == none) {
      pushToCompletionQueue();
   }

   return d_next_task_op == none;
}

/*
 ***********************************************************************
 ***********************************************************************
 */
template<class TYPE>
void
AsyncCommPeer<TYPE>::checkMPIParams()
{
   if (getPrimaryTag() < 0 || getSecondaryTag() < 0) {
      TBOX_ERROR("AsyncCommPeer: Invalid MPI tag values "
         << d_tag0 << " and " << d_tag1
         << "\nUse setMPITag() to set it.");
   }
   if (getMPI().getCommunicator() == MPI_COMM_NULL) {
      TBOX_ERROR("AsyncCommPeer: Invalid MPI communicator value "
         << d_mpi.getCommunicator() << "\nUse setCommunicator() to set it.");
   }
   if (getPeerRank() < 0) {
      TBOX_ERROR("AsyncCommPeer: Invalid peer rank "
         << d_peer_rank << "\nUse setPeerRank() to set it.");
   }
   if (getPeerRank() == getMPI().getRank() && !SAMRAI_MPI::usingMPI()) {
      TBOX_ERROR("AsyncCommPeer: Peer rank cannot be the local rank\n"
         << "when running without MPI.");
   }
}

/*
 ***********************************************************************
 ***********************************************************************
 */
template<class TYPE>
void
AsyncCommPeer<TYPE>::logCurrentState(
   std::ostream& co) const
{
   SAMRAI_MPI::Request * const req = getRequestPointer();
   co << "State=" << 10 * d_base_op + d_next_task_op
      << "  tag-0=" << d_tag0
      << "  tag-1=" << d_tag1
      << "  communicator=" << d_mpi.getCommunicator()
      << "  extern. buff=" << d_external_buf
      << "  size=" << d_full_count
      << "  request,status-0=" << (void *)req[0]
      << "  request,status-1=" << (void *)req[1]
   ;
   co << '\n';
}

/*
 ****************************************************************
 ****************************************************************
 */
template<class TYPE>
void
AsyncCommPeer<TYPE>::setMPITag(
   const int tag0,
   const int tag1)
{
   if (!isDone()) {
      TBOX_ERROR("Resetting the MPI tag is not allowed\n"
         << "during pending communications");
   }
   d_tag0 = tag0;
   d_tag1 = tag1;
}

/*
 ****************************************************************
 ****************************************************************
 */
template<class TYPE>
void
AsyncCommPeer<TYPE>::setMPI(
   const SAMRAI_MPI& mpi)
{
   if (!isDone()) {
      TBOX_ERROR("Resetting the MPI object is not allowed\n"
         << "during pending communications");
   }
   d_mpi = mpi;
}

/*
 ****************************************************************
 ****************************************************************
 */
template<class TYPE>
void
AsyncCommPeer<TYPE>::setPeerRank(
   int peer_rank)
{
   if (!isDone()) {
      TBOX_ERROR("Resetting the peer is not allowed\n"
         << "during pending communications");
   }
   d_peer_rank = peer_rank;
}

/*
 ****************************************************************
 ****************************************************************
 */
template<class TYPE>
size_t
AsyncCommPeer<TYPE>::getNumberOfFlexData(
   size_t number_of_type_data) const
{
   size_t number_of_flexdata = number_of_type_data * sizeof(TYPE);
   number_of_flexdata = number_of_flexdata / sizeof(FlexData)
      + (number_of_flexdata % sizeof(FlexData) > 0);
   return number_of_flexdata;
}

/*
 ***********************************************************************
 ***********************************************************************
 */
template<class TYPE>
int
AsyncCommPeer<TYPE>::getRecvSize() const
{
   if (getBaseOp() != recv) {
      TBOX_ERROR("AsyncCommPeer::getRecvSize() called without a\n"
         << "corresponding receive.");
   }
   return static_cast<int>(d_full_count);
}

/*
 ***********************************************************************
 ***********************************************************************
 */
template<class TYPE>
const TYPE *
AsyncCommPeer<TYPE>::getRecvData() const
{
   if (getBaseOp() != recv) {
      TBOX_ERROR("AsyncCommPeer::getRecvData() called without a\n"
         << "corresponding receive.");
   }
   if (!d_internal_buf) {
      TBOX_ERROR("AsyncCommPeer::getRecvData() after clearRecvData().\n");
   }
   return &d_internal_buf[0].d_t;
}

/*
 ***********************************************************************
 ***********************************************************************
 */
template<class TYPE>
void
AsyncCommPeer<TYPE>::clearRecvData()
{
   if (getNextTaskOp() != none) {
      TBOX_ERROR("AsyncCommPeer::clearRecvData() called during an\n"
         << "operation.");
   }
   if (d_internal_buf) {
#ifdef HAVE_UMPIRE
      d_allocator.deallocate(
         (char*)d_internal_buf, d_internal_buf_size * sizeof(FlexData));
#else
      free(d_internal_buf);
#endif
      d_internal_buf = 0;
   }
   if (d_count_buf) {
#ifdef HAVE_UMPIRE
      d_allocator.deallocate(
         (char*)d_count_buf, 2 * sizeof(FlexData));
#else
      free(d_count_buf);
#endif
      d_count_buf = 0;
   }
   d_first_recv_buf = 0;
}

/*
 ***********************************************************************
 ***********************************************************************
 */
template<class TYPE>
void
AsyncCommPeer<TYPE>::setSendTimer(
   const std::shared_ptr<Timer>& send_timer)
{
   t_send_timer = send_timer ? send_timer : t_default_send_timer;
}

/*
 ***********************************************************************
 ***********************************************************************
 */
template<class TYPE>
void
AsyncCommPeer<TYPE>::setRecvTimer(
   const std::shared_ptr<Timer>& recv_timer)
{
   t_recv_timer = recv_timer ? recv_timer : t_default_recv_timer;
}

/*
 ***********************************************************************
 ***********************************************************************
 */
template<class TYPE>
void
AsyncCommPeer<TYPE>::setWaitTimer(
   const std::shared_ptr<Timer>& wait_timer)
{
   t_wait_timer = wait_timer ? wait_timer : t_default_wait_timer;
}

template<class TYPE>
bool
AsyncCommPeer<TYPE>::isDone() const
{
   return d_next_task_op == none;
}

/*
 ***************************************************************************
 * Initialize static timers.
 ***************************************************************************
 */
template<class TYPE>
void
AsyncCommPeer<TYPE>::initializeCallback()
{
   t_default_send_timer = TimerManager::getManager()->
      getTimer("tbox::AsyncCommPeer::MPI_Isend()");
   t_default_recv_timer = TimerManager::getManager()->
      getTimer("tbox::AsyncCommPeer::MPI_Irecv()");
   t_default_wait_timer = TimerManager::getManager()->
      getTimer("tbox::AsyncCommPeer::MPI_Waitall()");
}

/*
 ***************************************************************************
 * Release static timers.  To be called by shutdown registry to make sure
 * memory for timers does not leak.
 ***************************************************************************
 */
template<class TYPE>
void
AsyncCommPeer<TYPE>::finalizeCallback()
{
   t_default_send_timer.reset();
   t_default_recv_timer.reset();
   t_default_wait_timer.reset();
}

template<class TYPE>
AsyncCommPeer<TYPE>::FlexData::FlexData()
{
#ifdef DEBUG_INITIALIZE_UNDEFINED
   memset(&d_i, 0, std::max(sizeof(int), sizeof(TYPE)));
#endif
}

}
}

#if !defined(__BGL_FAMILY__) && defined(__xlC__)
/*
 * Unsuppress XLC warnings
 */
#pragma report(disable, CPPC5334)
#pragma report(disable, CPPC5328)
#endif

#endif
