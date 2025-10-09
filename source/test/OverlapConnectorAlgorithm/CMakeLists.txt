set (oca_sources
  main.cpp)

set (oca_depends
    SAMRAI_hier
    SAMRAI_geom
    SAMRAI_tbox)

if (ENABLE_OPENMP)
  set(oca_depends ${oca_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(oca_depends ${oca_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(oca_depends ${oca_depends} blt::hip)
endif ()

blt_add_executable(
  NAME overlap-connector-algorithm
  SOURCES ${oca_sources}
  DEPENDS_ON
    ${oca_depends})

target_compile_definitions(overlap-connector-algorithm PUBLIC TESTING=1)

set_target_properties(overlap-connector-algorithm PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME overlap-connector-algorithm
  EXECUTABLE overlap-connector-algorithm
  INPUTS ${test_inputs}
  PARALLEL TRUE)
