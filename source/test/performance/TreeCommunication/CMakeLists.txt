set (treecommunication_sources
  tcb.cpp)

set(treecommunication_depends SAMRAI_tbox)

if (ENABLE_OPENMP)
  set(treecommunication_depends ${treecommunication_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(treecommunication_depends ${treecommunication_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(treecommunication_depends ${treecommunication_depends} blt::hip)
endif ()



blt_add_executable(
  NAME treecommunication
  SOURCES ${treecommunication_sources}
  DEPENDS_ON ${treecommunication_depends})

target_compile_definitions(treecommunication PUBLIC TESTING=1)

set_target_properties(treecommunication PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME treecommunication
  EXECUTABLE treecommunication
  INPUTS ${test_inputs}
  PARALLEL TRUE)

