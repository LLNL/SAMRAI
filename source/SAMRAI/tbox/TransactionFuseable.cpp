#include "SAMRAI/tbox/TransactionFuseable.h"

namespace SAMRAI {
namespace tbox {

void
TransactionFuseable::setKernelFuser(StagedKernelFusers* fuser)
{
  d_fuser = fuser;
}

StagedKernelFusers*
TransactionFuseable::getKernelFuser()
{
  return d_fuser;
}

}
}
