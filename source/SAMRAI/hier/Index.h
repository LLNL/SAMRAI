/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and LICENSE.
 *
 * Copyright:     (c) 1997-2025 Lawrence Livermore National Security, LLC
 * Description:   Interface for the AMR Index object
 *
 ************************************************************************/

#ifndef included_hier_Index
#define included_hier_Index

#include "SAMRAI/SAMRAI_config.h"

#include "SAMRAI/hier/IntVector.h"
#include "SAMRAI/tbox/Dimension.h"
#include "SAMRAI/tbox/Utilities.h"

namespace SAMRAI {
namespace hier {

/**
 * Class Index implements a simple n-dimensional integer vector in the
 * AMR index space.  Index is used as lower and upper bounds when
 * creating a box and also when iterating over the cells in a box.  An
 * Index is essentially an integer vector but it carries along the
 * notion of indexing into AMR's abstract index space.
 *
 * @see Box
 * @see BoxIterator
 * @see IntVector
 */

class Index
{
public:

   typedef tbox::Dimension::dir_t dir_t;

   /**
    * @brief Creates an uninitialized Index.
    */
   explicit Index(
      const tbox::Dimension& dim);

   /**
    * @brief Construct an Index with all components equal to the argument.
    */
   Index(
      const tbox::Dimension& dim,
      const int value);

   /**
    * @brief Construct a two-dimensional Index with the value (i,j).
    */
   Index(
      const int i,
      const int j);

   /**
    * @brief Construct a three-dimensional Index with the value (i,j,k).
    */
   Index(
      const int i,
      const int j,
      const int k);

   /**
    * @brief Construct an n-dimensional Index with the values copied
    *        from the integer tbox::Array i of size n.
    *
    * The dimension of the constructed Index will be equal to the size of the
    * argument vector.
    *
    * @pre i.size() > 0
    */
   explicit Index(
      const std::vector<int>& i);

   /**
    * @brief The copy constructor creates an Index equal to the argument.
    */
   Index(
      const Index& rhs);

   /**
    * @brief Construct an Index equal to the argument IntVector.
    *
    * @pre rhs.getNumBlocks() == 1
    */
   explicit Index(
      const IntVector& rhs);

   /**
    * @brief Construct an Index equal to the argument array.
    */
   Index(
      const tbox::Dimension& dim,
      const int array[]);

   /**
    * @brief The assignment operator sets the Index equal to the argument.
    *
    * @pre getDim() == rhs.getDim()
    */
   Index&
   operator = (
      const Index& rhs)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      for (unsigned int i = 0; i < d_dim.getValue(); ++i) {
         d_index[i] = rhs.d_index[i];
      }
      return *this;
   }

   /**
    * @brief The assignment operator sets the Index equal to the argument
    *        IntVector.
    *
    * @pre getDim() == rhs.getDim()
    * @pre rhs.getNumBlocks() == 1
    */
   Index&
   operator = (
      const IntVector& rhs)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      TBOX_ASSERT(rhs.getNumBlocks() == 1);
      for (unsigned int i = 0; i < d_dim.getValue(); ++i) {
         d_index[i] = rhs[i];
      }
      return *this;
   }

   /**
    * @brief The Index destructor does nothing interesting.
    */
   virtual ~Index();

   /**
    * @brief Returns true if all components are equal to a given integer.
    */
   bool
   operator == (
      const Index& rhs) const
   {
      bool result = true;
      for (unsigned int i = 0; result && (i < getDim().getValue()); ++i) {
         result = d_index[i] == rhs.d_index[i];
      }
      return result;
   }

   /**
    * @brief Returns true if some components are not equal to a given integer.
    */
   bool
   operator != (
      const Index& rhs) const
   {
      return !(*this == rhs);
   }

   /**
    * @brief Plus-equals operator for an Index and an integer vector.
    *
    * @pre getDim() == rhs.getDim()
    * @pre rhs.getNumBlocks() == 1
    */
   Index&
   operator += (
      const IntVector& rhs)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      TBOX_ASSERT(rhs.getNumBlocks() == 1);
      for (unsigned int i = 0; i < d_dim.getValue(); ++i) {
         d_index[i] += rhs[i];
      }
      return *this;
   }

   /**
    * @brief Plus operator for an Index and an integer vector.
    *
    * @pre getDim() == rhs.getDim()
    * @pre rhs.getNumBlocks() == 1
    */
   Index
   operator + (
      const IntVector& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      TBOX_ASSERT(rhs.getNumBlocks() == 1);
      Index tmp = *this;
      tmp += rhs;
      return tmp;
   }

   /**
    * @brief Plus-equals operator for an Index
    *
    * @pre getDim() == rhs.getDim()
    */
   Index&
   operator += (
      const Index& rhs)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      for (unsigned int i = 0; i < d_dim.getValue(); ++i) {
         d_index[i] += rhs.d_index[i];
      }
      return *this;
   }

   /**
    * @brief Plus operator for an Index and an another Index
    *
    * @pre getDim() == rhs.getDim()
    */
   Index
   operator + (
      const Index& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      Index tmp = *this;
      tmp += rhs;
      return tmp;
   }

   /**
    * @brief Plus-equals operator for an Index and an integer.
    */
   Index&
   operator += (
      const int rhs)
   {
      for (unsigned int i = 0; i < d_dim.getValue(); ++i) {
         d_index[i] += rhs;
      }
      return *this;
   }

   /**
    * @brief Plus operator for an Index and an integer.
    */
   Index
   operator + (
      const int rhs) const
   {
      Index tmp = *this;
      tmp += rhs;
      return tmp;
   }

   /**
    * @brief Minus-equals operator for an Index
    *
    * @pre getDim() == rhs.getDim()
    */
   Index&
   operator -= (
      const Index& rhs)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      for (unsigned int i = 0; i < d_dim.getValue(); ++i) {
         d_index[i] -= rhs.d_index[i];
      }
      return *this;
   }

   /**
    * @brief Minus operator for an Index
    *
    * @pre getDim() == rhs.getDim()
    */
   Index
   operator - (
      const Index& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      Index tmp = *this;
      tmp -= rhs;
      return tmp;
   }

   /**
    * @brief Minus-equals operator for an Index and an integer vector.
    *
    * @pre getDim() == rhs.getDim()
    * @pre rhs.getNumBlocks() == 1
    */
   Index&
   operator -= (
      const IntVector& rhs)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      TBOX_ASSERT(rhs.getNumBlocks() == 1);
      for (unsigned int i = 0; i < d_dim.getValue(); ++i) {
         d_index[i] -= rhs[i];
      }
      return *this;
   }

   /**
    * @brief Minus operator for an Index and an integer vector.
    *
    * @pre getDim() == rhs.getDim()
    * @pre rhs.getNumBlocks() == 1
    */
   Index
   operator - (
      const IntVector& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      TBOX_ASSERT(rhs.getNumBlocks() == 1);
      Index tmp = *this;
      tmp -= rhs;
      return tmp;
   }

   /**
    * @brief Minus-equals operator for an Index and an integer.
    */
   Index&
   operator -= (
      const int rhs)
   {
      for (unsigned int i = 0; i < d_dim.getValue(); ++i) {
         d_index[i] -= rhs;
      }
      return *this;
   }

   /**
    * @brief Minus operator for an Index and an integer.
    */
   Index
   operator - (
      const int rhs) const
   {
      Index tmp = *this;
      tmp -= rhs;
      return tmp;
   }

   /**
    * @brief Times-equals operator for an Index and an integer vector.
    *
    * @pre getDim() == rhs.getDim()
    * @pre rhs.getNumBlocks() == 1
    */
   Index&
   operator *= (
      const IntVector& rhs)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      TBOX_ASSERT(rhs.getNumBlocks() == 1);
      for (unsigned int i = 0; i < getDim().getValue(); ++i) {
         d_index[i] *= rhs[i];
      }
      return *this;
   }

   /**
    * @brief Times operator for an Index and an integer vector.
    *
    * @pre getDim() == rhs.getDim()
    * @pre rhs.getNumBlocks() == 1
    */
   Index
   operator * (
      const IntVector& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      TBOX_ASSERT(rhs.getNumBlocks() == 1);
      Index tmp = *this;
      tmp *= rhs;
      return tmp;
   }

   /**
    * @brief Times-equals operator for an Index and an integer.
    */
   Index&
   operator *= (
      const int rhs)
   {
      for (unsigned int i = 0; i < getDim().getValue(); ++i) {
         d_index[i] *= rhs;
      }
      return *this;
   }

   /**
    * @brief Times operator for an Index and an integer.
    */
   Index
   operator * (
      const int rhs) const
   {
      Index tmp = *this;
      tmp *= rhs;
      return tmp;
   }

   /**
    * @brief Assign-quotient operator for an Index and an integer vector.
    *
    * @pre getDim() == rhs.getDim()
    * @pre rhs.getNumBlocks() == 1
    */
   Index&
   operator /= (
      const IntVector& rhs)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      TBOX_ASSERT(rhs.getNumBlocks() == 1);
      for (unsigned int i = 0; i < getDim().getValue(); ++i) {
         d_index[i] /= rhs[i];
      }
      return *this;
   }

   /**
    * @brief Quotient operator for an Index and an integer vector.
    *
    * @pre getDim() == rhs.getDim()
    * @pre rhs.getNumBlocks() == 1
    */
   Index
   operator / (
      const IntVector& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      TBOX_ASSERT(rhs.getNumBlocks() == 1);
      Index tmp = *this;
      tmp /= rhs;
      return tmp;
   }

   /**
    * @brief Assign-quotient operator for an Index and an integer.
    */
   Index&
   operator /= (
      const int rhs)
   {
      for (unsigned int i = 0; i < getDim().getValue(); ++i) {
         d_index[i] /= rhs;
      }
      return *this;
   }

   /**
    * @brief Quotient operator for an Index and an integer.
    */
   Index
   operator / (
      const int rhs) const
   {
      Index tmp = *this;
      tmp /= rhs;
      return tmp;
   }

   /**
    * @brief Return the specified component of the Index.
    *
    * @pre (i >= 0) && (i < getDim().getValue())
    */
   int&
   operator [] (
      const unsigned int i)
   {
      TBOX_ASSERT(i < getDim().getValue());
      return d_index[i];
   }

   /**
    * @brief Return the specified component of the vector as a const reference.
    *
    * @pre (i >= 0) && (i < getDim().getValue())
    */
   const int&
   operator [] (
      const unsigned int i) const
   {
      TBOX_ASSERT(i < getDim().getValue());
      return d_index[i];
   }

   /**
    * @brief Return the specified component of the Index.
    *
    * @pre (i >= 0) && (i < getDim().getValue())
    */
   int&
   operator () (
      const unsigned int i)
   {
      TBOX_ASSERT(i < getDim().getValue());
      return d_index[i];
   }

   /**
    * @brief Return the specified component of the Index as a const reference.
    *
    * @pre (i >= 0) && (i < getDim().getValue())
    */
   const int&
   operator () (
      const unsigned int i) const
   {
      TBOX_ASSERT(i < getDim().getValue());
      return d_index[i];
   }

   /**
    * @brief Returns true if each integer in Index is greater than
    *        corresponding integer in comparison Index.
    *
    * @pre getDim() == rhs.getDim()
    */
   bool
   operator > (
      const Index& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      bool result = true;
      for (unsigned int i = 0; result && (i < getDim().getValue()); ++i) {
         result = result && (d_index[i] > rhs.d_index[i]);
      }
      return result;
   }

   /**
    * @brief Returns true if each integer in Index is greater or equal to
    *        corresponding integer in comparison Index.
    *
    * @pre getDim() == rhs.getDim()
    */
   bool
   operator >= (
      const Index& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      bool result = true;
      for (unsigned int i = 0; result && (i < getDim().getValue()); ++i) {
         result = result && (d_index[i] >= rhs.d_index[i]);
      }
      return result;
   }

   /**
    * @brief Returns true if each integer in Index is less than
    *        corresponding integer in comparison Index.
    *
    * @pre getDim() == rhs.getDim()
    */
   bool
   operator < (
      const Index& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      bool result = true;
      for (unsigned int i = 0; result && (i < getDim().getValue()); ++i) {
         result = result && (d_index[i] < rhs.d_index[i]);
      }
      return result;
   }

   /**
    * @brief Returns true if each integer in Index is less than or equal to
    *        corresponding integer in comparison Index.
    *
    * @pre getDim() == rhs.getDim()
    */
   bool
   operator <= (
      const Index& rhs) const
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      bool result = true;
      for (unsigned int i = 0; result && (i < getDim().getValue()); ++i) {
         result = result && (d_index[i] <= rhs.d_index[i]);
      }
      return result;
   }

   /**
    * @brief Set Index the component-wise minimum of two Index objects.
    *
    * @pre getDim() == rhs.getDim()
    */
   void
   min(
      const Index& rhs)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      for (dir_t i = 0; i < getDim().getValue(); ++i) {
         if (rhs.d_index[i] < d_index[i]) {
            d_index[i] = rhs.d_index[i];
         }
      }
   }

   /**
    * @brief Set Index the component-wise maximum of two Index objects.
    *
    * @pre getDim() == rhs.getDim()
    */
   void
   max(
      const Index& rhs)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, rhs);
      for (unsigned int i = 0; i < getDim().getValue(); ++i) {
         if (rhs.d_index[i] > d_index[i]) {
            d_index[i] = rhs.d_index[i];
         }
      }
   }

   /*!
    * @brief Coarsen the Index by a given ratio.
    *
    * For positive indices, this is the same as dividing by the ratio.
    *
    * @pre getDim() == ratio.getDim()
    * @pre rhs.getNumBlocks() == 1
    */
   Index&
   coarsen(
      const IntVector& ratio)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(*this, ratio);
      TBOX_ASSERT(ratio.getNumBlocks() == 1);
      for (unsigned int d = 0; d < getDim().getValue(); ++d) {
         (*this)(d) = coarsen((*this)(d), ratio(d));
      }
      return *this;
   }

   /*!
    * @brief Return an Index of zeros of the specified dimension.
    *
    * Can be used to avoid object creation overheads.
    */
   static const Index&
   getZeroIndex(
      const tbox::Dimension& dim)
   {
      return *(s_zeros[dim.getValue() - 1]);
   }

   /*!
    * @brief Return an Index of ones of the specified dimension.
    *
    * Can be used to avoid object creation overheads.
    */
   static const Index&
   getOneIndex(
      const tbox::Dimension& dim)
   {
      return *(s_ones[dim.getValue() - 1]);
   }

   /*!
    * @brief Return an Index with minimum index values for the
    * specified dimension.
    *
    * Can be used to avoid object creation overheads.
    */
   static const Index&
   getMinIndex(
      const tbox::Dimension& dim)
   {
      return *(s_mins[dim.getValue() - 1]);
   }

   /*!
    * @brief Return an Index with maximum index values for the
    * specified dimension.
    *
    * Can be used to avoid object creation overheads.
    */
   static const Index&
   getMaxIndex(
      const tbox::Dimension& dim)
   {
      return *(s_maxs[dim.getValue() - 1]);
   }

   /*!
    * @brief Coarsen an Index by a given ratio.
    *
    * For positive indices, this is the same as dividing by the ratio.
    *
    * @pre index.getDim() == ratio.getDim()
    * @pre rhs.getNumBlocks() == 1
    */
   static Index
   coarsen(
      const Index& index,
      const IntVector& ratio)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(index, ratio);
      TBOX_ASSERT(ratio.getNumBlocks() == 1);
      tbox::Dimension dim(index.getDim());
      Index tmp(dim);
      for (unsigned int d = 0; d < dim.getValue(); ++d) {
         tmp(d) = coarsen(index(d), ratio(d));
      }
      return tmp;
   }

   /*!
    * @brief Get the Dimension of the Index
    */
   const tbox::Dimension&
   getDim() const
   {
      return d_dim;
   }

   /**
    * @brief Read an input stream into an Index.
    */
   friend std::istream&
   operator >> (
      std::istream& s,
      Index& rhs);

   /**
    * @brief Write an integer index into an output stream.  The format for
    *        the output is (i0,...,in) for an n-dimensional index.
    */
   friend std::ostream&
   operator << (
      std::ostream& s,
      const Index& rhs);


   /**
    * @brief Utility function to take the minimum of two Index objects.
    *
    * @pre a.getDim() == b.getDim()
    */
   static Index
   min(
      const Index& a,
      const Index& b)
   {
      TBOX_ASSERT_OBJDIM_EQUALITY2(a, b);
      Index tmp = a;
      tmp.min(b);
      return tmp;
   }

private:
   /*
    * Unimplemented default constructor
    */
   Index();

   static int
   coarsen(
      const int index,
      const int ratio)
   {
      return index < 0 ? (index + 1) / ratio - 1 : index / ratio;
   }

   /*!
    * @brief Initialize static objects and register shutdown routine.
    *
    * Only called by StartupShutdownManager.
    *
    */
   static void
   initializeCallback();

   /*!
    * @brief Method registered with ShutdownRegister to cleanup statics.
    *
    * Only called by StartupShutdownManager.
    *
    */
   static void
   finalizeCallback();

   static Index* s_zeros[SAMRAI::MAX_DIM_VAL];
   static Index* s_ones[SAMRAI::MAX_DIM_VAL];

   static Index* s_maxs[SAMRAI::MAX_DIM_VAL];
   static Index* s_mins[SAMRAI::MAX_DIM_VAL];

   static tbox::StartupShutdownManager::Handler
      s_initialize_finalize_handler;

   tbox::Dimension d_dim;

   int d_index[SAMRAI::MAX_DIM_VAL];


};

}
}

#endif
