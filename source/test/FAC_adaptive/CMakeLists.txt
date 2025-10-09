set (facadaptive_sources
  AdaptivePoisson.cpp
  GaussianFcn.cpp
  PoissonGaussianDiffcoefSolution.cpp
  PoissonGaussianSolution.cpp
  PoissonMultigaussianSolution.cpp
  PoissonPolynomialSolution.cpp
  PoissonSineSolution.cpp
  QuarticFcn.cpp
  SinusoidFcn.cpp
  main.cpp
  patchFcns.cpp
  setArrayData.cpp)

set(facadaptive_depends testlib)
set(facadaptive_depends ${facadaptive_depends} ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(facadaptive_depends ${facadaptive_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(facadaptive_depends ${facadaptive_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(facadaptive_depends ${facadaptive_depends} blt::hip)
endif ()

blt_add_executable(
  NAME facadaptive
  SOURCES ${facadaptive_sources}
  DEPENDS_ON
    ${facadaptive_depends})

target_compile_definitions(facadaptive PUBLIC TESTING=1)

set_target_properties(facadaptive PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME facadaptive
  EXECUTABLE facadaptive
  INPUTS ${test_inputs}
  PARALLEL TRUE)
