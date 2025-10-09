set (convdiff_sources
  ConvDiff.cpp
  main.cpp
  MainRestartData.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/compute_rhs2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/compute_rhs3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/init2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/init3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/rkstep2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/rkstep3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/tag_cells2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/tag_cells3d.f)

process_m4(NAME fortran/compute_rhs2d)
process_m4(NAME fortran/compute_rhs3d)
process_m4(NAME fortran/init2d)
process_m4(NAME fortran/init3d)
process_m4(NAME fortran/rkstep2d)
process_m4(NAME fortran/rkstep3d)
process_m4(NAME fortran/tag_cells2d)
process_m4(NAME fortran/tag_cells3d)

set(convdiff_depends testlib)
set(convdiff_depends ${convdiff_depends} ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(convdiff_depends ${convdiff_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(convdiff_depends ${convdiff_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(convdiff_depends ${convdiff_depends} blt::hip)
endif ()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTESTING=1") 

blt_add_executable(
  NAME convdiff
  SOURCES ${convdiff_sources}
  DEPENDS_ON ${convdiff_depends})

target_include_directories(
  convdiff
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/applications/ConvDiff)

set_target_properties(convdiff PROPERTIES LINKER_LANGUAGE CXX)

target_compile_definitions(convdiff PRIVATE TESTING=1)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)
file (GLOB test_baselines ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*boxes*)

execute_process(COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/test_inputs)
execute_process(COMMAND ln -s ${test_baselines} ${CMAKE_CURRENT_BINARY_DIR}/test_inputs)

samrai_add_tests(
  NAME convdiff
  EXECUTABLE convdiff
  INPUTS ${test_inputs}
  PARALLEL TRUE)

