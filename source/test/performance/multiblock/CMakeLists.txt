set (multiblock_sources
  main.cpp
  MblkGeometry.cpp
  MblkLinAdv.cpp
  SkeletonOutersideDoubleWeightedAverage.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/stufprobc.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/trace1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/trace2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/trace3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/grad2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/grad3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/flux2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/flux3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/fluxcorner3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/stable2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/stable3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/init2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/init3d.f)

process_m4(NAME fortran/stufprobc)
process_m4(NAME fortran/trace1d)
process_m4(NAME fortran/trace2d)
process_m4(NAME fortran/trace3d)
process_m4(NAME fortran/grad2d)
process_m4(NAME fortran/grad3d)
process_m4(NAME fortran/flux2d)
process_m4(NAME fortran/flux3d)
process_m4(NAME fortran/fluxcorner3d)
process_m4(NAME fortran/stable2d)
process_m4(NAME fortran/stable3d)
process_m4(NAME fortran/init2d)
process_m4(NAME fortran/init3d)

set(multiblock_depends testlib)
set(multiblock_depends ${multiblock_depends} ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(multiblock_depends ${multiblock_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(multiblock_depends ${multiblock_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(multiblock_depends ${multiblock_depends} blt::hip)
endif ()


blt_add_executable(
  NAME multiblock
  SOURCES ${multiblock_sources}
  DEPENDS_ON ${multiblock_depends})

target_compile_definitions(multiblock PUBLIC TESTING=1)

set_target_properties(multiblock PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME multiblock
  EXECUTABLE multiblock
  INPUTS ${test_inputs}
  PARALLEL TRUE)

