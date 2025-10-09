set (nonlinear_sources
  main.cpp
  ModifiedBratuProblem.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/FACjacobian1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/FACjacobian2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/FACjacobian3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/adjcrsfineoffdiag1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/bcFluxCopy1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/bcFluxCopy2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/bcFluxCopy3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/bcFluxFix1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/bcFluxFix2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/bcFluxFix3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/bratufunc1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/bratufunc2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/bratufunc3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/err1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/err2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/err3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalBratu1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalBratu2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalBratu3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalDiffusionCoef1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalDiffusionCoef2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalDiffusionCoef3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalExponential1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalExponential2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalExponential3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalF1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalF2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalF3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalFaceFluxes1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalFaceFluxes2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalFaceFluxes3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalJv1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalJv2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalJv3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalSource1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalSource2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/evalSource3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/setbc1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/setbc2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/setbc3d.f
  )

process_m4(NAME fortran/FACjacobian1d)
process_m4(NAME fortran/FACjacobian2d)
process_m4(NAME fortran/FACjacobian3d)
process_m4(NAME fortran/adjcrsfineoffdiag1d)
process_m4(NAME fortran/bcFluxCopy1d)
process_m4(NAME fortran/bcFluxCopy2d)
process_m4(NAME fortran/bcFluxCopy3d)
process_m4(NAME fortran/bcFluxFix1d)
process_m4(NAME fortran/bcFluxFix2d)
process_m4(NAME fortran/bcFluxFix3d)
process_m4(NAME fortran/bratufunc1d)
process_m4(NAME fortran/bratufunc2d)
process_m4(NAME fortran/bratufunc3d)
process_m4(NAME fortran/err1d)
process_m4(NAME fortran/err2d)
process_m4(NAME fortran/err3d)
process_m4(NAME fortran/evalBratu1d)
process_m4(NAME fortran/evalBratu2d)
process_m4(NAME fortran/evalBratu3d)
process_m4(NAME fortran/evalDiffusionCoef1d)
process_m4(NAME fortran/evalDiffusionCoef2d)
process_m4(NAME fortran/evalDiffusionCoef3d)
process_m4(NAME fortran/evalExponential1d)
process_m4(NAME fortran/evalExponential2d)
process_m4(NAME fortran/evalExponential3d)
process_m4(NAME fortran/evalF1d)
process_m4(NAME fortran/evalF2d)
process_m4(NAME fortran/evalF3d)
process_m4(NAME fortran/evalFaceFluxes1d)
process_m4(NAME fortran/evalFaceFluxes2d)
process_m4(NAME fortran/evalFaceFluxes3d)
process_m4(NAME fortran/evalJv1d)
process_m4(NAME fortran/evalJv2d)
process_m4(NAME fortran/evalJv3d)
process_m4(NAME fortran/evalSource1d)
process_m4(NAME fortran/evalSource2d)
process_m4(NAME fortran/evalSource3d)
process_m4(NAME fortran/setbc1d)
process_m4(NAME fortran/setbc2d)
process_m4(NAME fortran/setbc3d)

set(nonlinear_depends ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(nonlinear_depends ${nonlinear_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(nonlinear_depends ${nonlinear_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(nonlinear_depends ${nonlinear_depends} blt::hip)
endif ()

blt_add_executable(
  NAME nonlinear
  SOURCES ${nonlinear_sources}
  DEPENDS_ON
    ${nonlinear_depends})

target_compile_definitions(nonlinear PUBLIC TESTING=1)

set_target_properties(nonlinear PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME nonlinear
  EXECUTABLE nonlinear
  INPUTS ${test_inputs}
  PARALLEL TRUE
  EXTRA_ARG "-skip-petscrc")
