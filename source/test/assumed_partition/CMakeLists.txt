
set (assumed_partition_depends SAMRAI_geom SAMRAI_hier SAMRAI_tbox)

if (ENABLE_OPENMP)
  set(assumed_partition_depends ${assumed_partition_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(assumed_partition_depends ${assumed_partition_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(assumed_partition_depends ${assumed_partition_depends} blt::hip)
endif ()

blt_add_executable(
  NAME assumed_partition
  SOURCES main.cpp
  DEPENDS_ON ${assumed_partition_depends})

set_target_properties(assumed_partition PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories( assumed_partition
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/assumed_partition)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME assumed_partition
  EXECUTABLE assumed_partition
  INPUTS ${test_inputs}
  PARALLEL TRUE)
