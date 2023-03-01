/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright
 * information, see COPYRIGHT and LICENSE.
 *
 * Copyright:     (c) 1997-2021 Lawrence Livermore National Security, LLC
 * Description:   Singleton kernel fuser
 *
 ************************************************************************/

#include "SAMRAI/tbox/ScheduleKernelFuser.h"


namespace SAMRAI {
namespace tbox {

ScheduleKernelFuser* ScheduleKernelFuser::s_schedule_kernel_fuser_instance(nullptr);

StartupShutdownManager::Handler
ScheduleKernelFuser::s_startup_handler(
    0,
    ScheduleKernelFuser::startupCallback,
    0,
    0,
    tbox::StartupShutdownManager::priorityArenaManager);

void
ScheduleKernelFuser::startupCallback()
{
  ScheduleKernelFuser::getInstance()->initialize();
}

void
ScheduleKernelFuser::shutdownCallback()
{
   if (s_schedule_kernel_fuser_instance) {
      delete s_schedule_kernel_fuser_instance;
   }
   s_schedule_kernel_fuser_instance = nullptr;
}

ScheduleKernelFuser *
ScheduleKernelFuser::getInstance()
{
   if (!s_schedule_kernel_fuser_instance) {
      s_schedule_kernel_fuser_instance = new ScheduleKernelFuser();
   }
   return s_schedule_kernel_fuser_instance;
}

ScheduleKernelFuser::~ScheduleKernelFuser()
{
   delete d_kernel_fuser;
   d_kernel_fuser = nullptr;
}

void
ScheduleKernelFuser::initialize()
{
   d_kernel_fuser = new KernelFuser();
}


}
}

