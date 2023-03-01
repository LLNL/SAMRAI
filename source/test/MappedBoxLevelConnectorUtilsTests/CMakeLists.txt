set (mapped_boxlevel_sources
  main-mblcu.cpp)

blt_add_executable(
  NAME mblcu
  SOURCES ${mapped_boxlevel_sources}
  DEPENDS_ON
    SAMRAI_hier
    SAMRAI_geom
    SAMRAI_mesh
    SAMRAI_tbox
    cuda)

target_compile_definitions(mblcu PUBLIC TESTING=1)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME mblcu
  EXECUTABLE mblcu
  INPUTS ${test_inputs}
  PARALLEL TRUE)
