set (meshgeneration_sources
  mg.cpp)

set(meshgeneration_depends testlib)
set(meshgeneration_depends ${meshgeneration_depends} ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(meshgeneration_depends ${meshgeneration_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(meshgeneration_depends ${meshgeneration_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(meshgeneration_depends ${meshgeneration_depends} blt::hip)
endif ()

blt_add_executable(
  NAME meshgeneration
  SOURCES ${meshgeneration_sources}
  DEPENDS_ON ${meshgeneration_depends})

target_compile_definitions(meshgeneration PUBLIC TESTING=1)

set_target_properties(meshgeneration PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME meshgeneration
  EXECUTABLE meshgeneration
  INPUTS ${test_inputs}
  PARALLEL TRUE)

