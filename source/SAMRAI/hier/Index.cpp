/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and LICENSE.
 *
 * Copyright:     (c) 1997-2025 Lawrence Livermore National Security, LLC
 * Description:   Interface for the AMR Index object
 *
 ************************************************************************/
#include "SAMRAI/hier/Index.h"
#include "SAMRAI/tbox/MathUtilities.h"
#include "SAMRAI/tbox/StartupShutdownManager.h"

namespace SAMRAI {
namespace hier {

Index * Index::s_zeros[SAMRAI::MAX_DIM_VAL];
Index * Index::s_ones[SAMRAI::MAX_DIM_VAL];

Index * Index::s_mins[SAMRAI::MAX_DIM_VAL];
Index * Index::s_maxs[SAMRAI::MAX_DIM_VAL];

tbox::StartupShutdownManager::Handler
Index::s_initialize_finalize_handler(
   Index::initializeCallback,
   0,
   0,
   Index::finalizeCallback,
   tbox::StartupShutdownManager::priorityTimers);

Index::Index(
   const tbox::Dimension& dim):
   d_dim(dim)
{
#ifdef DEBUG_INITIALIZE_UNDEFINED
   for (int i = 0; i < SAMRAI::MAX_DIM_VAL; ++i) {
      d_index[i] = tbox::MathUtilities<int>::getMin();
   }
#endif
}

Index::Index(
   const tbox::Dimension& dim,
   const int value):
   d_dim(dim)
{
   for (int i = 0; i < d_dim.getValue(); ++i) {
      d_index[i] = value;
   }

#ifdef DEBUG_INITIALIZE_UNDEFINED
   for (int i = d_dim.getValue(); i < SAMRAI::MAX_DIM_VAL; ++i) {
      d_index[i] = tbox::MathUtilities<int>::getMin();
   }
#endif
}

Index::Index(
   const int i,
   const int j):
   d_dim(2)
{
   TBOX_DIM_ASSERT(tbox::Dimension::getMaxDimension() >= tbox::Dimension(2));

   d_index[0] = i;
   if (SAMRAI::MAX_DIM_VAL > 1) {
      d_index[1] = j;
   }
}

Index::Index(
   const int i,
   const int j,
   const int k):
   d_dim(3)
{
   TBOX_DIM_ASSERT(tbox::Dimension::getMaxDimension() >= tbox::Dimension(3));

   d_index[0] = i;
   if (SAMRAI::MAX_DIM_VAL > 1) {
      d_index[1] = j;
   }

   if (SAMRAI::MAX_DIM_VAL > 2) {
      d_index[2] = k;
   }

}

Index::Index(
   const std::vector<int>& a):
   d_dim(static_cast<unsigned short>(a.size()))
{
   TBOX_ASSERT(a.size() > 0);
   for (int i = 0; i < d_dim.getValue(); ++i) {
      d_index[i] = a[i];
   }

#ifdef DEBUG_INITIALIZE_UNDEFINED
   for (int i = d_dim.getValue(); i < SAMRAI::MAX_DIM_VAL; ++i) {
      d_index[i] = tbox::MathUtilities<int>::getMin();
   }
#endif
}

Index::Index(
   const tbox::Dimension& dim,
   const int array[]):
   d_dim(dim)
{
   for (int i = 0; i < d_dim.getValue(); ++i) {
      d_index[i] = array[i];
   }
}

Index::Index(
   const Index& rhs):
   d_dim(rhs.d_dim)
{
   for (int i = 0; i < d_dim.getValue(); ++i) {
      d_index[i] = rhs.d_index[i];
   }
}

Index::Index(
   const IntVector& rhs):
   d_dim(rhs.getDim())
{
   TBOX_ASSERT(rhs.getNumBlocks() == 1);
   for (int i = 0; i < d_dim.getValue(); ++i) {
      d_index[i] = rhs[i];
   }
}

Index::~Index()
{
}

void
Index::initializeCallback()
{
   for (unsigned short d = 0; d < SAMRAI::MAX_DIM_VAL; ++d) {
      s_zeros[d] = new Index(tbox::Dimension(static_cast<unsigned short>(d + 1)), 0);
      s_ones[d] = new Index(tbox::Dimension(static_cast<unsigned short>(d + 1)), 1);

      s_mins[d] = new Index(tbox::Dimension(static_cast<unsigned short>(d + 1)),
            tbox::MathUtilities<int>::getMin());
      s_maxs[d] = new Index(tbox::Dimension(static_cast<unsigned short>(d + 1)),
            tbox::MathUtilities<int>::getMax());
   }
}

void
Index::finalizeCallback()
{
   for (int d = 0; d < SAMRAI::MAX_DIM_VAL; ++d) {
      delete s_zeros[d];
      delete s_ones[d];

      delete s_mins[d];
      delete s_maxs[d];
   }
}

std::istream&
operator >> (
   std::istream& s,
   Index& rhs)
{
   while (s.get() != '(') ;

   for (int i = 0; i < rhs.getDim().getValue(); ++i) {
      s >> rhs(i);
      if (i < rhs.getDim().getValue() - 1)
         while (s.get() != ',') ;
   }

   while (s.get() != ')') ;

   return s;
}

std::ostream& operator << (
   std::ostream& s,
   const Index& rhs)
{
   s << '(';

   for (int i = 0; i < rhs.getDim().getValue(); ++i) {
      s << rhs(i);
      if (i < rhs.getDim().getValue() - 1)
         s << ",";
   }
   s << ')';

   return s;
}


}
}
