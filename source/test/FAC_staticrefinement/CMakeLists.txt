set (facstaticrefinement_sources
  FACPoisson.cpp
  main.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/facpoisson2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/facpoisson3d.f)

set(facstaticrefinement_depends ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(facstaticrefinement_depends ${facstaticrefinement_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(facstaticrefinement_depends ${facstaticrefinement_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(facstaticrefinement_depends ${facstaticrefinement_depends} blt::hip)
endif ()

process_m4(NAME fortran/facpoisson2d)
process_m4(NAME fortran/facpoisson3d)

blt_add_executable(
  NAME facstaticrefinement
  SOURCES ${facstaticrefinement_sources}
  DEPENDS_ON
    ${facstaticrefinement_depends})

target_compile_definitions(facstaticrefinement PUBLIC TESTING=1)

set_target_properties(facstaticrefinement PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME facstaticrefinement
  EXECUTABLE facstaticrefinement
  INPUTS ${test_inputs}
  PARALLEL TRUE)
