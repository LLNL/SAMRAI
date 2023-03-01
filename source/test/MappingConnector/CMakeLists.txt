set (mapping_connector_sources
  main-modify.cpp)

blt_add_executable(
  NAME mapping-connector
  SOURCES ${mapping_connector_sources}
  DEPENDS_ON
    SAMRAI_hier
    SAMRAI_geom
    SAMRAI_mesh
    SAMRAI_tbox
    cuda)

target_compile_definitions(mapping-connector PUBLIC TESTING=1)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME mapping-connector
  EXECUTABLE mapping-connector
  INPUTS ${test_inputs}
  PARALLEL TRUE)
