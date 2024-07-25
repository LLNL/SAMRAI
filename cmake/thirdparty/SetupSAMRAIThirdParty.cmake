set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/thirdparty/")

# MPI is setup by BLT
if (MPI_FOUND)
  set(HAVE_MPI True)
else ()
  set(LACKS_MPI True)
endif ()

# OpenMP is set up by BLT
if (ENABLE_OPENMP)
  if (OPENMP_FOUND)
    set(HAVE_OPENMP True)
  endif ()
endif ()

# UMPIRE
if (ENABLE_UMPIRE OR umpire_DIR)
  find_package(umpire REQUIRED)

  set (HAVE_UMPIRE True)
  set (ENABLE_UMPIRE On)

endif ()

# RAJA
if (ENABLE_RAJA OR RAJA_DIR)
  if (NOT ENABLE_UMPIRE)
    message(FATAL_ERROR "RAJA support requires UMPIRE.")
  endif ()

  find_package(RAJA REQUIRED)

  set (raja_depends_on)
  if (ENABLE_CUDA)
    list (APPEND raja_depends cuda)
  endif ()

  if (ENABLE_HIP)
    list (APPEND raja_depends hip)
  endif ()

  if (ENABLE_OPENMP)
    list (APPEND raja_depends openmp)
  endif ()

  if (RAJA_FOUND)
    set (HAVE_RAJA True)
    set (ENABLE_RAJA ON)

    blt_register_library(
      NAME RAJA
      INCLUDES ${RAJA_INCLUDE_DIR}
      LIBRARIES RAJA
      DEPENDS_ON ${raja_depends})
  endif ()
endif ()

if (ENABLE_CALIPER OR caliper_DIR)
  find_package(caliper REQUIRED)

  set (HAVE_CALIPER True)
  set (ENABLE_CALIPER On)

  blt_register_library(
    NAME caliper
    INCLUDES ${CALIPER_INCLUDE_DIRS}
    LIBRARIES caliper)
endif ()

# CUDA is setup by BLT
if (ENABLE_CUDA)
  if (NOT ENABLE_UMPIRE)
    message(FATAL_ERROR "CUDA support requires UMPIRE")
  endif ()

  if (CUDA_FOUND)
    set (HAVE_CUDA True)
  endif ()
  if (ENABLE_NVTX_REGIONS)
    set (ENABLE_NVTX_REGIONS True)
  endif ()
endif ()

# HIP is setup by BLT
if (ENABLE_HIP)
  if (NOT ENABLE_UMPIRE)
    message(FATAL_ERROR "HIP support requires UMPIRE")
  endif ()

  set (HAVE_HIP True)

  if (ENABLE_SAMRAI_DEVICE_ALLOC)
     set (USE_DEVICE_ALLOCATOR True)
  endif ()
endif ()

# HDF5
if (ENABLE_HDF5)
  if (NOT ENABLE_MPI)
    message(FATAL_ERROR "HDF5 requires MPI.")
  endif ()

  find_package(HDF5 REQUIRED)

  if(HDF5_FOUND)
    set (HAVE_HDF5 True)

    blt_register_library(
      NAME hdf5
      INCLUDES ${HDF5_INCLUDE_DIRS}
      LIBRARIES ${HDF5_C_LIBRARIES})
  endif ()
endif ()


#HAVE_HYPRE
if (ENABLE_HYPRE OR HYPRE_DIR)
  find_package(HYPRE REQUIRED)
  # TODO: Ensure this is set in SAMRAI_config.h...

  if(HYPRE_FOUND)
    set (HAVE_HYPRE True)
    set (ENABLE_HYPRE ON) 

    blt_register_library(
      NAME HYPRE
      INCLUDES ${HYPRE_INCLUDE_DIRS}
      LIBRARIES ${HYPRE_LIBRARIES})
  endif ()
endif ()

# OpenMP
if (ENABLE_OPENMP)
  if (OPENMP_FOUND)
    set(HAVE_OPENMP True)
  endif ()
endif ()

#HAVE_PETSC
if (ENABLE_PETSC OR PETSC_DIR)
  find_package(PETSc REQUIRED)

  if (PETSC_FOUND)
    set (HAVE_PETSC True)
    set (ENABLE_PETSC ON)

    blt_register_library(
      NAME PETSc
      INCLUDES ${PETSC_INCLUDE_DIRS}
      LIBRARIES ${PETSC_LIBRARIES})
  endif ()
endif()


#HAVE_SILO
if (ENABLE_SILO OR SILO_DIR)
  find_package(SILO REQUIRED)

  if (SILO_FOUND)
    set (HAVE_SILO True)
    set (ENABLE_SILO ON)

    blt_register_library(
      NAME silo
      INCLUDES ${SILO_INCLUDE_DIRS}
      LIBRARIES ${SILO_LIBRARIES})
  endif ()
endif ()


#HAVE_SUNDIALS
if (ENABLE_SUNDIALS OR SUNDIALS_DIR)
  find_package(SUNDIALS REQUIRED)
  if (SUNDIALS_FOUND)
    set (HAVE_SUNDIALS True)
    set (ENABLE_SUNDIALS ON)

    blt_register_library(
      NAME SUNDIALS
      INCLUDES ${SUNDIALS_INCLUDE_DIRS}
      LIBRARIES ${SUNDIALS_LIBRARIES})
  endif ()
endif ()


#SAMRAI_HAVE_CONDUIT
if (ENABLE_CONDUIT OR CONDUIT_DIR)
  find_package(CONDUIT REQUIRED)
  if (CONDUIT_FOUND)
    set (SAMRAI_HAVE_CONDUIT True)
    set (ENABLE_CONDUIT ON)

    blt_register_library(
      NAME CONDUIT
      INCLUDES ${CONDUIT_INCLUDE_DIRS}
      LIBRARIES ${CONDUIT_LIBRARIES})
  endif ()
endif ()
