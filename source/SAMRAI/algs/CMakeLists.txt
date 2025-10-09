set (algs_headers
  HyperbolicLevelIntegrator.h
  HyperbolicPatchStrategy.h
  ImplicitEquationStrategy.h
  ImplicitIntegrator.h
  MethodOfLinesIntegrator.h
  MethodOfLinesPatchStrategy.h
  OuteredgeSumTransaction.h
  OuteredgeSumTransactionFactory.h
  OuternodeSumTransaction.h
  OuternodeSumTransactionFactory.h
  PatchBoundaryEdgeSum.h
  PatchBoundaryNodeSum.h
  TimeRefinementIntegrator.h
  TimeRefinementIntegratorConnectorWidthRequestor.h
  TimeRefinementLevelStrategy.h)

set (algs_sources
  HyperbolicLevelIntegrator.cpp
  HyperbolicPatchStrategy.cpp
  ImplicitEquationStrategy.cpp
  ImplicitIntegrator.cpp
  MethodOfLinesIntegrator.cpp
  MethodOfLinesPatchStrategy.cpp
  OuteredgeSumTransaction.cpp
  OuteredgeSumTransactionFactory.cpp
  OuternodeSumTransaction.cpp
  OuternodeSumTransactionFactory.cpp
  PatchBoundaryEdgeSum.cpp
  PatchBoundaryNodeSum.cpp
  TimeRefinementIntegrator.cpp
  TimeRefinementIntegratorConnectorWidthRequestor.cpp
  TimeRefinementLevelStrategy.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/algs_nodeouternodeops2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/algs_nodeouternodeops3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/algs_upfluxsum1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/algs_upfluxsum2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/algs_upfluxsum3d.f)

set (algs_depends
  SAMRAI_hier
  SAMRAI_tbox
  SAMRAI_pdat)

if (ENABLE_CUDA)
  set (algs_depends ${algs_depends} cuda)
endif ()

if (ENABLE_HIP)
  set (algs_depends ${algs_depends} blt::hip)
endif ()

process_m4(NAME fortran/algs_nodeouternodeops2d)
process_m4(NAME fortran/algs_nodeouternodeops3d)
process_m4(NAME fortran/algs_upfluxsum1d)
process_m4(NAME fortran/algs_upfluxsum2d)
process_m4(NAME fortran/algs_upfluxsum3d)

blt_add_library( NAME SAMRAI_algs
  SOURCES ${algs_sources}
  HEADERS ${algs_headers}
  DEPENDS_ON ${algs_depends})

set_target_properties(SAMRAI_algs PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories( SAMRAI_algs
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>
  $<INSTALL_INTERFACE:include>)

install(TARGETS SAMRAI_algs
  EXPORT SAMRAITargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES ${algs_headers}
  DESTINATION include/SAMRAI/algs)
