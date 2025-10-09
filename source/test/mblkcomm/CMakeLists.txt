set (mblkcomm_sources
  CellMultiblockTest.cpp
  EdgeMultiblockTest.cpp
  FaceMultiblockTest.cpp
  main.cpp
  MultiblockTester.cpp
  NodeMultiblockTest.cpp
  PatchMultiblockTestStrategy.cpp
  SideMultiblockTest.cpp)

set (mblkcomm_depends_on
  SAMRAI_hier
  SAMRAI_geom
  SAMRAI_pdat
  SAMRAI_mesh
  SAMRAI_tbox)

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(mblkcomm_depends_on ${mblkcomm_depends_on} openmp)
endif ()

if (ENABLE_CUDA)
  set(mblkcomm_depends_on ${mblkcomm_depends_on} cuda)
endif ()

if (ENABLE_HIP)
  set(mblkcomm_depends_on ${mblkcomm_depends_on} blt::hip)
endif ()

blt_add_executable(
  NAME mblkcomm
  SOURCES ${mblkcomm_sources}
  DEPENDS_ON
    ${mblkcomm_depends_on})

target_compile_definitions(mblkcomm PUBLIC TESTING=1)

set_target_properties(mblkcomm PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME mblkcomm
  EXECUTABLE mblkcomm
  INPUTS ${test_inputs}
  PARALLEL TRUE)
