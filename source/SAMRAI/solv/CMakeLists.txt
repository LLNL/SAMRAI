set (solv_headers
  CartesianRobinBcHelper.h
  CellPoissonFACOps.h
  CellPoissonFACSolver.h
  CellPoissonHypreSolver.h
  CVODEAbstractFunctions.h
  CVODESolver.h
  FACOperatorStrategy.h
  FACPreconditioner.h
  GhostCellRobinBcCoefs.h
  KINSOL_SAMRAIContext.h
  KINSOLAbstractFunctions.h
  KINSOLSolver.h
  LocationIndexRobinBcCoefs.h
  NonlinearSolverStrategy.h
  nvector.h
  PETSc_SAMRAIVectorReal.h
  PETSc_SAMRAIVectorReal.cpp
  PETScAbstractVectorReal.h
  PETScAbstractVectorReal.cpp
  PoissonSpecifications.h
  RobinBcCoefStrategy.h
  SAMRAIVectorReal.h
  SAMRAIVectorReal.cpp
  SimpleCellRobinBcCoefs.h
  SNES_SAMRAIContext.h
  SNESAbstractFunctions.h
  solv_NVector.h
  Sundials_SAMRAIVector.h
  SundialsAbstractVector.h)

set_source_files_properties(
  PETScAbstractVectorReal.cpp
  PETSc_SAMRAIVectorReal.cpp
  SAMRAIVectorReal.cpp
  PROPERTIES HEADER_FILE_ONLY TRUE)

set (solv_sources
  CVODEAbstractFunctions.cpp
  CVODESolver.cpp
  CartesianRobinBcHelper.cpp
  CellPoissonFACOps.cpp
  CellPoissonFACSolver.cpp
  CellPoissonHypreSolver.cpp
  FACOperatorStrategy.cpp
  FACPreconditioner.cpp
  GhostCellRobinBcCoefs.cpp
  KINSOLAbstractFunctions.cpp
  KINSOLSolver.cpp
  KINSOL_SAMRAIContext.cpp
  LocationIndexRobinBcCoefs.cpp
  NonlinearSolverStrategy.cpp
  PoissonSpecifications.cpp
  RobinBcCoefStrategy.cpp
  SNESAbstractFunctions.cpp
  SNES_SAMRAIContext.cpp
  SimpleCellRobinBcCoefs.cpp
  SundialsAbstractVector.cpp
  Sundials_SAMRAIVector.cpp
  solv_NVector.cpp
  fortran/solv_cartesianrobinbchelper2d.f
  fortran/solv_cartesianrobinbchelper3d.f
  fortran/solv_cellpoissonfacops2d.f
  fortran/solv_cellpoissonfacops3d.f
  fortran/solv_cellpoissonhypresolver2d.f
  fortran/solv_cellpoissonhypresolver3d.f)

set_source_files_properties(
  fortran/solv_cartesianrobinbchelper2d.f
  fortran/solv_cartesianrobinbchelper3d.f
  fortran/solv_cellpoissonfacops2d.f
  fortran/solv_cellpoissonfacops3d.f
  fortran/solv_cellpoissonhypresolver2d.f
  fortran/solv_cellpoissonhypresolver3d.f
  PROPERTIES
  LANGUAGE
  Fortran)

set (solv_depends
  SAMRAI_hier
  SAMRAI_math
  SAMRAI_tbox
  SAMRAI_xfer)

if (ENABLE_CUDA)
  set (solv_depends ${solv_depends} cuda)
endif ()

if (ENABLE_HIP)
  set (solv_depends ${solv_depends} blt::hip)
endif ()

if (ENABLE_HYPRE)
  list (APPEND solv_depends HYPRE)
endif()

if (ENABLE_SUNDIALS)
  list (APPEND solv_depends SUNDIALS)
endif()

if (ENABLE_PETSC)
  list (APPEND solv_depends PETSc)
endif()

blt_add_library(
  NAME SAMRAI_solv
  SOURCES ${solv_sources}
  HEADERS ${solv_headers}
  DEPENDS_ON ${solv_depends})

set_target_properties(SAMRAI_solv PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(
  SAMRAI_solv
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>
  $<INSTALL_INTERFACE:include>)

install(TARGETS SAMRAI_solv
  EXPORT SAMRAITargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES ${solv_headers}
  DESTINATION include/SAMRAI/solv)
