/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and LICENSE.
 *
 * Copyright:     (c) 1997-2020 Lawrence Livermore National Security, LLC
 * Description:   Abstract base class for all schedule transactions
 *
 ************************************************************************/

#ifndef included_tbox_TransactionFuseable
#define included_tbox_TransactionFuseable

#include "SAMRAI/SAMRAI_config.h"

#include "SAMRAI/tbox/Transaction.h"
#include "SAMRAI/tbox/KernelFuser.h"

#include <iostream>

namespace SAMRAI {
namespace tbox {

class TransactionFuseable :
  public Transaction
{
public:
  void setKernelFuser(KernelFuser* fuser);
  KernelFuser* getKernelFuser();

private:
  KernelFuser* d_fuser{nullptr};
};

}
}

#endif