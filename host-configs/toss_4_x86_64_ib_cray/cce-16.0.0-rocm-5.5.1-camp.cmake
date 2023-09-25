set(CMAKE_CXX_COMPILER "/usr/tce/packages/cce-tce/cce-16.0.0/bin/crayCC" CACHE PATH "")
set(CMAKE_C_COMPILER "/usr/tce/packages/cce-tce/cce-16.0.0/bin/craycc" CACHE PATH "")
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "")
set(BLT_CXX_STD "c++14" CACHE STRING "")
set(ENABLE_TESTS Off CACHE BOOL "")
set(ENABLE_CLANG_CUDA Off CACHE BOOL "")
set(ENABLE_CUDA Off CACHE BOOL "")
set(ENABLE_HIP On CACHE BOOL "")
set(HIP_ROOT_DIR "/opt/rocm-5.5.1/hip" CACHE PATH "")
set(HIP_HIPCC_FLAGS "-D__HIP_ROCclr__ -D__HIP_PLATFORM_AMD__ -DCAMP_USE_PLATFORM_DEFAULT_STREAM -D__HIP_ARCH_GFX90A__=1 --rocm-path=/opt/rocm-5.6.0 -std=c++14 -x hip --offload-arch=gfx90a" CACHE STRING "")
set(CMAKE_HIP_ARCHITECTURES "gfx90a" CACHE STRING "")
