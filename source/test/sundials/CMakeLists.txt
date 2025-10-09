set (sundials_sources
  main.cpp
  CVODEModel.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/FACjacobian2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/FACjacobian3d.f)

process_m4(NAME fortran/FACjacobian2d)
process_m4(NAME fortran/FACjacobian3d)

set(sundials_depends ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(sundials_depends ${sundials_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(sundials_depends ${sundials_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(sundials_depends ${sundials_depends} blt::hip)
endif ()


blt_add_executable(
  NAME sundials_test
  SOURCES ${sundials_sources}
  DEPENDS_ON ${sundials_depends})

target_include_directories( sundials_test
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/sundials)

target_compile_definitions(sundials_test PUBLIC TESTING=1)

set_target_properties(sundials_test PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME sundials_test
  EXECUTABLE sundials_test
  INPUTS ${test_inputs}
  PARALLEL TRUE)
