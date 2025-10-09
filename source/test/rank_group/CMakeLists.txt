set (rank_group_sources
  main.cpp)

set(rank_group_depends ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(rank_group_depends ${rank_group_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(rank_group_depends ${rank_group_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(rank_group_depends ${rank_group_depends} blt::hip)
endif ()

blt_add_executable(
  NAME rank_group
  SOURCES ${rank_group_sources}
  DEPENDS_ON ${rank_group_depends})

target_compile_definitions(rank_group PUBLIC TESTING=1)

set_target_properties(rank_group PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME rank_group
  EXECUTABLE rank_group
  INPUTS ${test_inputs}
  PARALLEL TRUE)
