set ( fill_pattern_sources
  main-fill-pattern.cpp)

set(fill_pattern_depends ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(fill_pattern_depends ${fill_pattern_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(fill_pattern_depends ${fill_pattern_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(fill_pattern_depends ${fill_pattern_depends} blt::hip)
endif ()


blt_add_executable(
  NAME fill_pattern
  SOURCES ${fill_pattern_sources}
  DEPENDS_ON ${fill_pattern_depends})

target_compile_definitions(fill_pattern PUBLIC TESTING=1)

set_target_properties(fill_pattern PROPERTIES LINKER_LANGUAGE CXX)

if(ENABLE_MPI)
  set(TASKS 1)
else()
  set(TASKS 0)
endif()

blt_add_test(
  NAME fill_pattern
  COMMAND fill_pattern
  NUM_MPI_TASKS ${TASKS})

