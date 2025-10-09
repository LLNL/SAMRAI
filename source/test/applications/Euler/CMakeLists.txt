set (euler_sources
  Euler.cpp
  main.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/avgint2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/avgint3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/flaten1d2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/flaten1d3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/flux2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/flux3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/fluxcorner3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/grad2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/grad3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/init2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/init3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/stable2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/stable3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/stufprobc.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/trace1d2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/trace1d3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/trace2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/trace3d.f)

process_m4(NAME fortran/avgint2d)
process_m4(NAME fortran/avgint3d)
process_m4(NAME fortran/flaten1d2d)
process_m4(NAME fortran/flaten1d3d)
process_m4(NAME fortran/flux2d)
process_m4(NAME fortran/flux3d)
process_m4(NAME fortran/fluxcorner3d)
process_m4(NAME fortran/grad2d)
process_m4(NAME fortran/grad3d)
process_m4(NAME fortran/init2d)
process_m4(NAME fortran/init3d)
process_m4(NAME fortran/stable2d)
process_m4(NAME fortran/stable3d)
process_m4(NAME fortran/stufprobc)
process_m4(NAME fortran/trace1d2d)
process_m4(NAME fortran/trace1d3d)
process_m4(NAME fortran/trace2d)
process_m4(NAME fortran/trace3d)

set(euler_depends testlib)
set(euler_depends ${euler_depends} ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(euler_depends ${euler_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(euler_depends ${euler_depends} cuda)
endif ()
if (ENABLE_HIP)
  set(euler_depends ${euler_depends} blt::hip)
endif ()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTESTING=1") 

blt_add_executable(
  NAME euler
  SOURCES ${euler_sources}
  DEPENDS_ON ${euler_depends})

target_include_directories( euler
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/applications/Euler)

set_target_properties(euler PROPERTIES LINKER_LANGUAGE CXX)

target_compile_definitions(euler PRIVATE TESTING=1)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)
file (GLOB test_baselines ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*boxes*)

if (NOT ENABLE_HDF5)
  list(FILTER test_inputs EXCLUDE REGEX .*restart.*d.input)
endif ()

execute_process(COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/test_inputs)
execute_process(COMMAND ln -s ${test_baselines} ${CMAKE_CURRENT_BINARY_DIR}/test_inputs)

samrai_add_tests(
  NAME euler
  EXECUTABLE euler
  INPUTS ${test_inputs}
  PARALLEL TRUE)

