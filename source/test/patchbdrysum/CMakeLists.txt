set (patchbdrysum_sources
  main.cpp
  HierSumTest.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/edgeops2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/edgeops3d.f)

process_m4(NAME fortran/edgeops2d)
process_m4(NAME fortran/edgeops3d)

set(patchbdrysum_depends  ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(patchbdrysum_depends ${patchbdrysum_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(patchbdrysum_depends ${patchbdrysum_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(patchbdrysum_depends ${patchbdrysum_depends} blt::hip)
endif ()

blt_add_executable(
  NAME patchbdrysum-test
  SOURCES ${patchbdrysum_sources}
  DEPENDS_ON
    ${patchbdrysum_depends})

target_compile_definitions(patchbdrysum-test PUBLIC TESTING=1)

set_target_properties(patchbdrysum-test PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME patchbdrysum-test
  EXECUTABLE patchbdrysum-test
  INPUTS ${test_inputs}
  PARALLEL TRUE)
