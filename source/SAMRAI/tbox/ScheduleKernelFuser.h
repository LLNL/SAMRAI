#ifndef included_tbox_ScheduleKernelFuser
#define included_tbox_ScheduleKernelFuser

#include "SAMRAI/SAMRAI_config.h"

#include "SAMRAI/tbox/KernelFuser.h"

#ifdef HAVE_RAJA
#include "RAJA/RAJA.hpp"
#endif


namespace SAMRAI {
namespace tbox {

class ScheduleKernelFuser
{
public:

   static ScheduleKernelFuser* getInstance();

#ifdef HAVE_RAJA
   template<typename Kernel>
   void enqueue(int stage, int begin, int end, Kernel&& kernel) {
      d_kernel_fuser->enqueue(begin, end, kernel);
   }
#endif

   void launch()
   {
      d_kernel_fuser->launch();
   }

   void cleanup()
   {
      d_kernel_fuser->cleanup(); 
   }

   KernelFuser* getFuser()
   {
      return d_kernel_fuser;
   }

   void initialize();

protected:
   ScheduleKernelFuser()
   {
   }

   virtual ~ScheduleKernelFuser();


private:

   static void startupCallback();
   static void shutdownCallback();

   static ScheduleKernelFuser* s_schedule_kernel_fuser_instance;

   static StartupShutdownManager::Handler
   s_startup_handler;

   KernelFuser* d_kernel_fuser = nullptr;
};

}
}

#endif
