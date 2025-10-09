set (hypre_sources
  main.cpp
  HyprePoisson.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/hyprepoisson2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/hyprepoisson3d.f)

process_m4(NAME fortran/hyprepoisson2d)
process_m4(NAME fortran/hyprepoisson3d)

set(hypre_depends ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(hypre_depends ${hypre_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(hypre_depends ${hypre_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(hypre_depends ${hypre_depends} blt::hip)
endif ()

if (HAVE_HYPRE)
  set (hypre_depends ${hypre_depends} hypre)
endif ()

blt_add_executable(
  NAME hypre-test
  SOURCES ${hypre_sources}
  DEPENDS_ON ${hypre_depends})

target_compile_definitions(hypre-test PUBLIC TESTING=1)

set_target_properties(hypre-test PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME hypre-test
  EXECUTABLE hypre-test
  INPUTS ${test_inputs}
  PARALLEL TRUE)

