set (xfer_headers
  BoxGeometryVariableFillPattern.h
  CoarsenAlgorithm.h
  CoarsenClasses.h
  CoarsenCopyTransaction.h
  CoarsenPatchStrategy.h
  CoarsenSchedule.h
  CoarsenTransactionFactory.h
  CompositeBoundaryAlgorithm.h
  CompositeBoundarySchedule.h
  PatchInteriorVariableFillPattern.h
  PatchLevelBorderAndInteriorFillPattern.h
  PatchLevelBorderFillPattern.h
  PatchLevelEnhancedFillPattern.h
  PatchLevelFillPattern.h
  PatchLevelFullFillPattern.h
  PatchLevelInteriorFillPattern.h
  RefineAlgorithm.h
  RefineClasses.h
  RefineCopyTransaction.h
  RefinePatchStrategy.h
  RefineSchedule.h
  RefineScheduleConnectorWidthRequestor.h
  RefineTimeTransaction.h
  RefineTransactionFactory.h
  SingularityPatchStrategy.h
  StandardCoarsenTransactionFactory.h
  StandardRefineTransactionFactory.h
  VariableFillPattern.h)

set (xfer_sources
  BoxGeometryVariableFillPattern.cpp
  CoarsenAlgorithm.cpp
  CoarsenClasses.cpp
  CoarsenCopyTransaction.cpp
  CoarsenPatchStrategy.cpp
  CoarsenSchedule.cpp
  CoarsenTransactionFactory.cpp
  CompositeBoundaryAlgorithm.cpp
  CompositeBoundarySchedule.cpp
  PatchInteriorVariableFillPattern.cpp
  PatchLevelBorderAndInteriorFillPattern.cpp
  PatchLevelBorderFillPattern.cpp
  PatchLevelEnhancedFillPattern.cpp
  PatchLevelFillPattern.cpp
  PatchLevelFullFillPattern.cpp
  PatchLevelInteriorFillPattern.cpp
  RefineAlgorithm.cpp
  RefineClasses.cpp
  RefineCopyTransaction.cpp
  RefinePatchStrategy.cpp
  RefineSchedule.cpp
  RefineScheduleConnectorWidthRequestor.cpp
  RefineTimeTransaction.cpp
  RefineTransactionFactory.cpp
  SingularityPatchStrategy.cpp
  StandardCoarsenTransactionFactory.cpp
  StandardRefineTransactionFactory.cpp
  VariableFillPattern.cpp)

set (xfer_depends 
   SAMRAI_hier
   SAMRAI_tbox)

if (ENABLE_CUDA)
  set(xfer_depends ${xfer_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(xfer_depends ${xfer_depends} blt::hip)
endif ()

blt_add_library(
  NAME SAMRAI_xfer
  SOURCES ${xfer_sources}
  HEADERS ${xfer_headers}
  DEPENDS_ON ${xfer_depends})

target_include_directories(
  SAMRAI_xfer
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>
  $<INSTALL_INTERFACE:include>)

install(TARGETS SAMRAI_xfer
  EXPORT SAMRAITargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES ${xfer_headers}
  DESTINATION include/SAMRAI/xfer)
