set(lbcorrectness_sources
  main-lbcorrectness.cpp)

set(lbcorrectness_depends testlib)
set(lbcorrectness_depends ${lbcorrectness_depends} ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(lbcorrectness_depends ${lbcorrectness_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(lbcorrectness_depends ${lbcorrectness_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(lbcorrectness_depends ${lbcorrectness_depends} blt::hip)
endif ()

blt_add_executable(
  NAME lbcorrectness
  SOURCES ${lbcorrectness_sources}
  DEPENDS_ON ${lbcorrectness_depends})

target_compile_definitions(lbcorrectness PUBLIC TESTING=1)

set_target_properties(lbcorrectness PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)
file (GLOB test_baselines ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*baseline*)

execute_process(COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/test_inputs)
execute_process(COMMAND ln -s ${test_baselines} ${CMAKE_CURRENT_BINARY_DIR}/test_inputs)

samrai_add_tests(
  NAME lbcorrectness
  EXECUTABLE lbcorrectness
  INPUTS ${test_inputs}
  PARALLEL TRUE)
