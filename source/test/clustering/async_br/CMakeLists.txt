set ( async_br_sources
  main.cpp
  ABRTest.cpp)

set(async_br_depends testlib)
set(async_br_depends ${async_br_depends} ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(async_br_depends ${async_br_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(async_br_depends ${async_br_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(async_br_depends ${async_br_depends} blt::hip)
endif ()

blt_add_executable(
  NAME async_br
  SOURCES ${async_br_sources}
  DEPENDS_ON ${async_br_depends})

set_target_properties(async_br PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories( async_br
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/clustering/async_br)

target_compile_definitions(async_br PUBLIC TESTING=1)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME async_br
  EXECUTABLE async_br
  INPUTS ${test_inputs}
  PARALLEL TRUE)
