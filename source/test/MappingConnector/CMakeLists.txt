set (mapping_connector_sources
  main-modify.cpp)

set (mapping_connector_depends
    SAMRAI_hier
    SAMRAI_geom
    SAMRAI_mesh
    SAMRAI_tbox)

if (ENABLE_OPENMP)
  set(mapping_connector_depends ${mapping_connector_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(mapping_connector_depends ${mapping_connector_depends} cuda)
endif ()

blt_add_executable(
  NAME mapping-connector
  SOURCES ${mapping_connector_sources}
  DEPENDS_ON ${mapping_connector_depends})

target_compile_definitions(mapping-connector PUBLIC TESTING=1)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME mapping-connector
  EXECUTABLE mapping-connector
  INPUTS ${test_inputs}
  PARALLEL TRUE)
