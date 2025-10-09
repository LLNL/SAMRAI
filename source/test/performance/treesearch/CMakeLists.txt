set (treesearch_sources
  main.cpp)

set (treesearch_depends SAMRAI_hier SAMRAI_tbox)

if (ENABLE_OPENMP)
  set(treesearch_depends ${treesearch_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(treesearch_depends ${treesearch_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(treesearch_depends ${treesearch_depends} blt::hip)
endif ()

blt_add_executable(
  NAME treesearch
  SOURCES ${treesearch_sources}
  DEPENDS_ON ${treesearch_depends})

target_compile_definitions(treesearch PUBLIC TESTING=1)

set_target_properties(treesearch PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME treesearch
  EXECUTABLE treesearch
  INPUTS ${test_inputs}
  PARALLEL TRUE)
