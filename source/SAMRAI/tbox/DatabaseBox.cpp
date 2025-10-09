/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and LICENSE.
 *
 * Copyright:     (c) 1997-2025 Lawrence Livermore National Security, LLC
 * Description:   A box structure representing a portion of the AMR index space
 *
 ************************************************************************/

#include "SAMRAI/tbox/DatabaseBox.h"

namespace SAMRAI {
namespace tbox {

DatabaseBox::DatabaseBox()
{
   d_data.d_dimension = 0;
   for (int i = 0; i < MAX_DIM_VAL; ++i) {
      d_data.d_lo[i] = d_data.d_hi[i] = 0;
   }
}

DatabaseBox::DatabaseBox(
   const DatabaseBox& box)
{
   d_data = box.d_data;
}

DatabaseBox::DatabaseBox(
   const Dimension& dim,
   const int* lower,
   const int* upper)
{
   d_data.d_dimension = dim.getValue();
   for (int i = 0; i < d_data.d_dimension; i++) {
      d_data.d_lo[i] = lower[i];
      d_data.d_hi[i] = upper[i];
   }
   for (int j = d_data.d_dimension; j < SAMRAI::MAX_DIM_VAL; j++) {
      d_data.d_lo[j] = 0;
      d_data.d_hi[j] = 0;
   }
}

DatabaseBox::~DatabaseBox()
{
}

DatabaseBox&
DatabaseBox::operator = (
   const DatabaseBox& box)
{
   d_data = box.d_data;
   return *this;
}

bool
DatabaseBox::empty() const
{
   bool is_empty = (d_data.d_dimension == 0 ? true : false);
   for (int i = 0; i < d_data.d_dimension; i++) {
      if (d_data.d_hi[i] < d_data.d_lo[i]) is_empty = true;
   }
   return is_empty;
}

int
DatabaseBox::operator == (
   const DatabaseBox& box) const
{
   bool equals = (d_data.d_dimension == box.d_data.d_dimension);
   for (int i = 0; i < d_data.d_dimension; i++) {
      if (d_data.d_lo[i] != box.d_data.d_lo[i]) {
         equals = false;
      }
      if (d_data.d_hi[i] != box.d_data.d_hi[i]) {
         equals = false;
      }
   }
   return equals;
}

}
}
