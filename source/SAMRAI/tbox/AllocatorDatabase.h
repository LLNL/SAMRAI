/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and LICENSE.
 *
 * Copyright:     (c) 1997-2017 Lawrence Livermore National Security, LLC
 * Description:   Singleton database class for Umpire allocators 
 *
 ************************************************************************/

#ifndef included_tbox_AllocatorDatabase
#define included_tbox_AllocatorDatabase

#include "SAMRAI/SAMRAI_config.h"

#include "SAMRAI/tbox/StartupShutdownManager.h"
#include "SAMRAI/tbox/ResourceAllocator.h"

#ifdef HAVE_UMPIRE
#include "umpire/Allocator.hpp"
#include "umpire/TypedAllocator.hpp"
#endif

namespace SAMRAI {
namespace tbox {

/*!
 * @brief Singleton class holding allocators for common SAMRAI operation
 *
 * This class provides access to Umpire allocators that are used to allocate
 * data for specific operations that occur during runs of applications
 * using SAMRAI.  The main intent is to support coordination of data
 * allocations on the host and device when running with cuda-based GPU
 * features enabled.  When not running with GPUs, these allocators will
 * default to do regular allocations of CPU memory.
 *
 * Allocators defined here are:
 *
 * Device pool--A pool of memory on the device that can be used for
 * temporary data that is created inside of kernels running on the GPU.
 *
 * Stream allocator--Allocator for pinned memory for MPI buffers used
 * in communications launched by tbox::Schedule, most notably during the
 * execution of refine and coarsen schedules.
 *
 * Tag allocator--Allocator for memory for the tag data object created and
 * owned by GriddingAlgorithm and provided to applications.
 *
 * Default allocator--Allocator for a default location for memory for problem
 * application data.
 *
 * These allocators can be overriden by creating Umpire allocators with the
 * appropriate name prior to calling tbox::SAMRAIManager::initialize().
 * The names are samrai::temporary_data_allocator, samrai::stream_allocator,
 * samrai::tag_allocator, and samrai::data_allocator.  Please see the Umpire
 * documentation for details on how to create new allocators.
 *
 * The accessor methods for all except the Stream allocator return the type
 * tbox::ResourceAllocator, which is an alias for the type umpire::Allocator.
 * tbox::ResourceAllocator is defined as an empty struct when SAMRAI is built
 * without Umpire, so these methods may be still called from codes that are not
 * built with Umpire.
 */

class AllocatorDatabase
{
public:
   /*!
    * @brief Static accessor function to get pointer to the instance of
    * the singleton object.
    */
   static AllocatorDatabase* getDatabase();

   /*!
    * @brief Initialize the allocators.
    */
   void initialize();

   /*!
    * @brief Get the device pool allocator.
    */
   ResourceAllocator getDevicePool();

   /*!
    * @brief Get the stream allocator.
    */
#ifdef HAVE_UMPIRE
   umpire::TypedAllocator<char> getStreamAllocator();
#endif

   /*!
    * @brief Get the kernel fuser allocator.
    */
#ifdef HAVE_UMPIRE
   umpire::TypedAllocator<char> getKernelFuserAllocator();
#endif

   /*!
    * @brief Get a host allocator.
    */
#ifdef HAVE_UMPIRE
   umpire::TypedAllocator<char> getInternalHostAllocator();
#endif

   /*!
    * @brief Get the allocator for tag data.
    */
   ResourceAllocator getTagAllocator();

   /*!
    * @brief Get the default allocator, unified memory for CUDA-based builds
    * and CPU host memory for non-CUDA builds.
    */
   ResourceAllocator getDefaultAllocator();

protected:
   AllocatorDatabase() = default;

   virtual ~AllocatorDatabase();

private:
   static void startupCallback();
   static void shutdownCallback();

   static AllocatorDatabase* s_allocator_database_instance;

   static StartupShutdownManager::Handler
   s_startup_handler;
};

}
}

#endif
