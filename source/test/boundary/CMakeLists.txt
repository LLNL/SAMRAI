set ( boundary_sources
  main.cpp
  BoundaryDataTester.cpp)

set(boundary_depends ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(boundary_depends ${boundary_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(boundary_depends ${boundary_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(boundary_depends ${boundary_depends} blt::hip)
endif ()

set(boundary_depends ${boundary_depends} testlib)

blt_add_executable(
  NAME boundary
  SOURCES ${boundary_sources}
  DEPENDS_ON ${boundary_depends})

target_include_directories( boundary
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/boundary)

target_compile_definitions(boundary PUBLIC TESTING=1)

set_target_properties(boundary PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME boundary
  EXECUTABLE boundary
  INPUTS ${test_inputs}
  PARALLEL TRUE)
