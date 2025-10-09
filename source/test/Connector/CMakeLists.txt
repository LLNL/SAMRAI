set ( connector_sources
  main.cpp)

set (connector_depends SAMRAI_tbox SAMRAI_hier SAMRAI_geom)

if (ENABLE_OPENMP)
  set(connector_depends ${connector_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(connector_depends ${connector_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(connector_depends ${connector_depends} blt::hip)
endif ()


blt_add_executable(
  NAME Connector
  SOURCES ${connector_sources}
  DEPENDS_ON
    SAMRAI_tbox
    SAMRAI_hier
    SAMRAI_geom)

target_include_directories( Connector
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/Connector)

set_target_properties(Connector PROPERTIES LINKER_LANGUAGE CXX)

target_compile_definitions(Connector PUBLIC TESTING=1)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME Connector
  EXECUTABLE Connector
  INPUTS ${test_inputs}
  PARALLEL TRUE)
