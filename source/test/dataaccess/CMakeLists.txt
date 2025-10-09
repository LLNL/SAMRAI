set ( dataaccess_sources
  main.cpp)

set(dataaccess_depends ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(dataaccess_depends ${dataaccess_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(dataaccess_depends ${dataaccess_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(dataaccess_depends ${dataaccess_depends} blt::hip)
endif ()

blt_add_executable(
  NAME dataaccess
  SOURCES ${dataaccess_sources}
  DEPENDS_ON ${dataaccess_depends})

target_include_directories( dataaccess
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/dataaccess)

set_target_properties(dataaccess PROPERTIES LINKER_LANGUAGE CXX)

target_compile_definitions(dataaccess PUBLIC TESTING=1)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME dataaccess
  EXECUTABLE dataaccess
  INPUTS ${test_inputs}
  PARALLEL TRUE)
