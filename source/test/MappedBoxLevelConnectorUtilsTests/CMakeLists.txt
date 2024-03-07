set (mapped_boxlevel_sources
  main-mblcu.cpp)

set (mapped_boxlevel_depends
    SAMRAI_hier
    SAMRAI_geom
    SAMRAI_mesh
    SAMRAI_tbox)

if (ENABLE_OPENMP)
  set(mapped_boxlevel_depends ${mapped_boxlevel_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(mapped_boxlevel_depends ${mapped_boxlevel_depends} cuda)
endif ()

blt_add_executable(
  NAME mblcu
  SOURCES ${mapped_boxlevel_sources}
  DEPENDS_ON ${mapped_boxlevel_depends})

target_compile_definitions(mblcu PUBLIC TESTING=1)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME mblcu
  EXECUTABLE mblcu
  INPUTS ${test_inputs}
  PARALLEL TRUE)
