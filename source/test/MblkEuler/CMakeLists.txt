set (mblkeuler_sources
  main.cpp
  MblkEuler.cpp
  MblkGeometry.cpp
  boundaryconditions.f)

set(mblkeuler_depends testlib)
set(mblkeuler_depends ${mblkeuler_depends} ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(mblkeuler_depends ${mblkeuler_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(mblkeuler_depends ${mblkeuler_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(mblkeuler_depends ${mblkeuler_depends} blt::hip)
endif ()

blt_add_executable(
  NAME mblkeuler
  SOURCES ${mblkeuler_sources}
  DEPENDS_ON ${mblkeuler_depends})

target_compile_definitions(mblkeuler PUBLIC TESTING=1)

set_target_properties(mblkeuler PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME mblkeuler
  EXECUTABLE mblkeuler
  INPUTS ${test_inputs}
  PARALLEL TRUE)

