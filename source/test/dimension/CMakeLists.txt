set ( dimension_sources
  main.cpp)

set (dimension_depends SAMRAI_tbox)

if (ENABLE_OPENMP)
  set(dimension_depends ${dimension_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(dimension_depends ${dimension_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(dimension_depends ${dimension_depends} blt::hip)
endif ()

blt_add_executable(
  NAME dimension
  SOURCES ${dimension_sources}
  DEPENDS_ON ${dimension_depends})

set_target_properties(dimension PROPERTIES LINKER_LANGUAGE CXX)

target_compile_definitions(dimension PUBLIC TESTING=1)

if(ENABLE_MPI)
  set(TASKS 1)
else()
  set(TASKS 0)
endif()

blt_add_test(
  NAME dimension
  COMMAND dimension
  NUM_MPI_TASKS ${TASKS})
