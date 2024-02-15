set(ENABLE_MPI On CACHE BOOL "")
set(CMAKE_CXX_COMPILER "/usr/tce/packages/clang/clang-ibm-14.0.5/bin/clang++" CACHE PATH "")
set(CMAKE_C_COMPILER "/usr/tce/packages/clang/clang-ibm-14.0.5/bin/clang" CACHE PATH "")
set(CMAKE_CUDA_HOST_COMPILER "/usr/tce/packages/clang/clang-ibm-14.0.5/bin/clang++" CACHE PATH "")
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION Off CACHE BOOL "")
set(CMAKE_C_FLAGS "--gcc-toolchain=/usr/tce/packages/gcc/gcc-8.3.1 -std=gnu11 -O2 -mtune=power9  -mpower9-vector -fPIC" CACHE STRING "")
set(CMAKE_CXX_FLAGS "--gcc-toolchain=/usr/tce/packages/gcc/gcc-8.3.1 -std=c++14 -O2 -mtune=power9  -mpower9-vector -fPIC" CACHE STRING "")
set(CMAKE_FORTRAN_FLAGS "--gcc-toolchain=/usr/tce/packages/gcc/gcc-8.3.1 -O2 -qarch=pwr9 -qtune=pwr9" CACHE STRING "")
set(BLT_CXX_STD "c++14" CACHE STRING "")
set(CMAKE_CXX_STANDARD "14" CACHE STRING "")
set(CMAKE_CUDA_STANDARD "14" CACHE STRING "")
set(CMAKE_CUDA_FLAGS "-Xcompiler=--gcc-toolchain=/usr/tce/packages/gcc/gcc-8.3.1 -restrict -arch sm_70 -std=c++14 --expt-extended-lambda" CACHE STRING "")
set(ENABLE_C On CACHE BOOL "")
set(ENABLE_FORTRAN Off CACHE BOOL "")
set(ENABLE_CUDA On CACHE BOOL "")
set(ENABLE_OPENMP Off CACHE BOOL "")
set(ENABLE_EXAMPLES Off CACHE BOOL "")
set(ENABLE_TESTS Off CACHE BOOL "")
set(UMPIRE_ENABLE_SLIC Off CACHE BOOL "")
set(ENABLE_MPI On CACHE BOOL "")
set(CUDA_SEPARABLE_COMPILATION On CACHE BOOL "")
set(UMPIRE_ENABLE_LOGGING On CACHE BOOL "")
set(UMPIRE_ENABLE_BACKTRACE On CACHE BOOL "")
set(UMPIRE_ENABLE_IPC_SHARED_MEMORY On CACHE BOOL "")
set(CUDA_ARCHITECTURES "70" CACHE STRING "")
set(CMAKE_CUDA_ARCHITECTURES "70" CACHE STRING "")
set(BLT_CLANG_CUDA_ARCH "sm_70" CACHE STRING "")
set(CMAKE_CUDA_COMPILER "/usr/tce/packages/cuda/cuda-11.8.0/bin/nvcc" CACHE PATH "")
set(CUDA_TOOLKIT_ROOT_DIR "/usr/tce/packages/cuda/cuda-11.8.0" CACHE PATH "")
set(BLT_CMAKE_IMPLICIT_LINK_DIRECTORIES_EXCLUDE "/usr/tce/packages/gcc/gcc-4.9.3/lib64;/usr/tce/packages/gcc/gcc-4.9.3/lib64/gcc/powerpc64le-unknown-linux-gnu/4.9.3;/usr/tce/packages/gcc/gcc-4.9.3/gnu/lib64;/usr/tce/packages/gcc/gcc-4.9.3/gnu/lib64/gcc/powerpc64le-unknown-linux-gnu/4.9.3" CACHE STRING "")
