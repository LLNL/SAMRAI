set (mpi_on_sources
  main-runtime-on.cpp
  mpi-interface-tests.cpp)

set (mpi_off_sources
  main-runtime-off.cpp
  mpi-interface-tests.cpp)

set (mpi_disabled_sources
  main-runtime-disabled.cpp
  mpi-interface-tests.cpp)

set (samrai_mpi_depends SAMRAI_tbox)

if (ENABLE_OPENMP)
  set(samrai_mpi_depends ${samrai_mpi_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(samrai_mpi_depends ${samrai_mpi_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(samrai_mpi_depends ${samrai_mpi_depends} blt::hip)
endif ()


if(ENABLE_MPI)
  set(TASKS 1)
else()
  set(TASKS 0)
endif()

blt_add_executable(
  NAME mpi_on
  SOURCES ${mpi_on_sources}
  DEPENDS_ON ${samrai_mpi_depends})

blt_add_executable(
  NAME mpi_off
  SOURCES ${mpi_off_sources}
  DEPENDS_ON ${samrai_mpi_depends})

blt_add_executable(
  NAME mpi_disabled
  SOURCES ${mpi_disabled_sources}
  DEPENDS_ON ${samrai_mpi_depends})

target_compile_definitions(mpi_on PUBLIC TESTING=1)
target_compile_definitions(mpi_off PUBLIC TESTING=1)
target_compile_definitions(mpi_disabled PUBLIC TESTING=1)

set_target_properties(mpi_on PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(mpi_off PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(mpi_disabled PROPERTIES LINKER_LANGUAGE CXX)

if(ENABLE_MPI)
  set(TASKS 1)
else()
  set(TASKS 0)
endif()

blt_add_test(
  NAME mpi_on
  COMMAND mpi_on
  NUM_MPI_TASKS ${TASKS})

blt_add_test(
  NAME mpi_off
  COMMAND mpi_off
  NUM_MPI_TASKS ${TASKS})

blt_add_test(
  NAME mpi_disabled
  COMMAND mpi_disabled)
