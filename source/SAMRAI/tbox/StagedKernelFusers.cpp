/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and LICENSE.
 *
 * Copyright:     (c) 1997-2021 Lawrence Livermore National Security, LLC
 * Description:   Singleton kernel fuser
 *
 ************************************************************************/

#include "SAMRAI/tbox/StagedKernelFusers.h"


namespace SAMRAI {
namespace tbox {

StagedKernelFusers* StagedKernelFusers::s_staged_kernel_fusers_instance(nullptr);

StartupShutdownManager::Handler
StagedKernelFusers::s_startup_handler(
    0,
    StagedKernelFusers::startupCallback,
    0,
    0,
    tbox::StartupShutdownManager::priorityArenaManager);

void
StagedKernelFusers::startupCallback()
{
  StagedKernelFusers::getInstance()->initialize();
}

void
StagedKernelFusers::shutdownCallback()
{
   if (s_staged_kernel_fusers_instance) {
      delete s_staged_kernel_fusers_instance;
   }
   s_staged_kernel_fusers_instance = nullptr;
}

StagedKernelFusers *
StagedKernelFusers::getInstance()
{
   if (!s_staged_kernel_fusers_instance) {
      s_staged_kernel_fusers_instance = new StagedKernelFusers();
   }
   return s_staged_kernel_fusers_instance;
}

StagedKernelFusers::~StagedKernelFusers()
{
}

void
StagedKernelFusers::initialize()
{
}


}
}

