set (stencil_sources
  Stencil.cpp
  main.cpp)

set(stencil_depends ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(stencil_depends ${stencil_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(stencil_depends ${stencil_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(stencil_depends ${stencil_depends} blt::hip)
endif ()

if (ENABLE_CALIPER)
set(stencil_depends ${stencil_depends} caliper)
endif ()

blt_add_executable(
  NAME stencil
  SOURCES ${stencil_sources}
  DEPENDS_ON ${stencil_depends})

target_include_directories( stencil
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/applications/Stencil)

set_target_properties(stencil PROPERTIES LINKER_LANGUAGE CXX)


set (test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/box2d_adv.input
                 ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/box2d_debug.input
                 ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/step.2d.input
                 ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/box3d_2_30.input)
file (GLOB perf_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*_50_*input
                       ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*_20_*input)

#execute_process(COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/test_inputs)
#execute_process(COMMAND ln -s ${test_baselines} ${CMAKE_CURRENT_BINARY_DIR}/test_inputs)

if (ENABLE_PERF_TESTS)
  samrai_add_tests(
     NAME stencil
     EXECUTABLE stencil
     INPUTS ${perf_inputs}
     PERFORMANCE TRUE
     PARALLEL TRUE)
else()
  samrai_add_tests(
     NAME stencil
     EXECUTABLE stencil
     INPUTS ${test_inputs}
     PARALLEL TRUE)
endif()
