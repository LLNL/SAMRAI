# When provided to CMake using the -C argument, the command line must
# also have a -DTPL_DIR:PATH=[third party library path] argument to 
# identify the location of the installed raja, umpire, camp libraries.

set(ENABLE_MPI On CACHE BOOL "")
set(CMAKE_C_COMPILER "/usr/tce/packages/spectrum-mpi/spectrum-mpi-rolling-release-clang-ibm-14.0.5/bin/mpicc" CACHE PATH "")
set(CMAKE_CXX_COMPILER "/usr/tce/packages/spectrum-mpi/spectrum-mpi-rolling-release-clang-ibm-14.0.5/bin/mpicxx" CACHE PATH "")
set(CMAKE_Fortran_COMPILER "/usr/tce/packages/gcc/gcc-8.3.1/bin/gfortran" CACHE PATH "")
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "")
set(ENABLE_OPENMP Off CACHE BOOL "")
set(ENABLE_HDF5 On CACHE BOOL "")
set(ENABLE_CUDA On CACHE BOOL "")
set(CMAKE_CUDA_COMPILER "/usr/tce/packages/cuda/cuda-11.8.0/bin/nvcc" CACHE PATH "")
set(CUDA_TOOLKIT_ROOT_DIR "/usr/tce/packages/cuda/cuda-11.8.0" CACHE PATH "")
set(CUDA_ARCH "sm_70" CACHE STRING "")
set(CMAKE_CUDA_FLAGS "-Xcompiler=--gcc-toolchain=/usr/tce/packages/gcc/gcc-8.3.1" CACHE STRING "")
set(CUDA_SEPARABLE_COMPILATION On CACHE BOOL "")
set(ENABLE_RAJA On CACHE BOOL "")
set(ENABLE_UMPIRE On CACHE BOOL "")
set(CMAKE_EXPORT_COMPILE_COMMANDS On CACHE BOOL "")
set(CMAKE_C_FLAGS "--gcc-toolchain=/usr/tce/packages/gcc/gcc-8.3.1 -O2 -mtune=power9  -mpower9-vector -fPIC -Wl,-ldl,-lrt,-lpthread" CACHE STRING "")
set(CMAKE_CXX_FLAGS "--gcc-toolchain=/usr/tce/packages/gcc/gcc-8.3.1 -std=c++14 -O2 -mtune=power9  -mpower9-vector -fPIC -Wl,-ldl,-lrt,-lpthread -L/usr/tce/packages/gcc/gcc-8.3.1/rh/lib/gcc/ppc64le-redhat-linux/8" CACHE STRING "")
set(BLT_CXX_STD "c++14" CACHE STRING "")
set(ENABLE_TESTS On CACHE BOOL "") 
set(ENABLE_SAMRAI_TESTS On CACHE BOOL "")
set(MIN_TEST_PROCS "2" CACHE STRING "")
set(CUDA_ARCHITECTURES "70" CACHE STRING "")
set(CMAKE_CUDA_ARCHITECTURES "70" CACHE STRING "")
set(BLT_CLANG_CUDA_ARCH "sm_70" CACHE STRING "")
set(BLT_CMAKE_IMPLICIT_LINK_DIRECTORIES_EXCLUDE "/usr/tce/packages/gcc/gcc-4.9.3/lib64;/usr/tce/packages/gcc/gcc-4.9.3/lib64/gcc/powerpc64le-unknown-linux-gnu/4.9.3;/usr/tce/packages/gcc/gcc-4.9.3/gnu/lib64;/usr/tce/packages/gcc/gcc-4.9.3/gnu/lib64/gcc/powerpc64le-unknown-linux-gnu/4.9.3" CACHE STRING "")

