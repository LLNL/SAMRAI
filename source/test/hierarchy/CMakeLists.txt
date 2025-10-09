set (hierarchy_sources
  main.cpp
  HierarchyTester.cpp)

set(hierarchy_depends ${hierarchy_depends} ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(hierarchy_depends ${hierarchy_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(hierarchy_depends ${hierarchy_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(hierarchy_depends ${hierarchy_depends} blt::hip)
endif ()

blt_add_executable(
  NAME hierarchy
  SOURCES ${hierarchy_sources}
  DEPENDS_ON ${hierarchy_depends})

target_compile_definitions(hierarchy PUBLIC TESTING=1)

set_target_properties(hierarchy PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME hierarchy
  EXECUTABLE hierarchy
  INPUTS ${test_inputs}
  PARALLEL TRUE)
