/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and LICENSE.
 *
 * Copyright:     (c) 1997-2025 Lawrence Livermore National Security, LLC
 * Description:   Abstract base class for time interpolation operators.
 *
 ************************************************************************/
#include "SAMRAI/hier/TimeInterpolateOperator.h"

namespace SAMRAI {
namespace hier {

TimeInterpolateOperator::TimeInterpolateOperator(
   const std::string& name):
   d_name(name)
{
}

TimeInterpolateOperator::~TimeInterpolateOperator()
{
}

}
}
