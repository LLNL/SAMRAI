set (mblklinadv_sources
  MblkGeometry.cpp
  MblkLinAdv.cpp
  SkeletonOutersideDoubleWeightedAverage.cpp
  main.cpp)


set(mblklinadv_depends testlib)
set(mblklinadv_depends ${mblklinadv_depends} ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(mblklinadv_depends ${mblklinadv_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(mblklinadv_depends ${mblklinadv_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(mblklinadv_depends ${mblklinadv_depends} blt::hip)
endif ()

blt_add_executable(
  NAME mblklinadv
  SOURCES ${mblklinadv_sources}
  DEPENDS_ON ${mblklinadv_depends})

target_compile_definitions(mblklinadv PRIVATE TESTING=0) # Source still needs to be modified to work with autotester

set_target_properties(mblklinadv PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME mblklinadv
  EXECUTABLE mblklinadv
  INPUTS ${test_inputs}
  PARALLEL TRUE)
