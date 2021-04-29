#include "SAMRAI/tbox/TransactionFuseable.h"

namespace SAMRAI {
namespace tbox {

void
TransactionFuseable::setKernelFuser(KernelFuser* fuser)
{
  d_fuser = fuser;
}

KernelFuser*
TransactionFuseable::getKernelFuser()
{
  return d_fuser;
}

}
}