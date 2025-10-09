set (math_headers
  ArrayDataBasicOps.cpp
  ArrayDataBasicOps.h
  ArrayDataMiscellaneousOpsReal.cpp
  ArrayDataMiscellaneousOpsReal.h
  ArrayDataNormOpsComplex.h
  ArrayDataNormOpsInteger.h
  ArrayDataNormOpsReal.cpp
  ArrayDataNormOpsReal.h
  HierarchyCellDataOpsComplex.h
  HierarchyCellDataOpsInteger.h
  HierarchyCellDataOpsReal.cpp
  HierarchyCellDataOpsReal.h
  HierarchyDataOpsComplex.h
  HierarchyDataOpsInteger.h
  HierarchyDataOpsManager.h
  HierarchyDataOpsReal.cpp
  HierarchyDataOpsReal.h
  HierarchyEdgeDataOpsComplex.h
  HierarchyEdgeDataOpsInteger.h
  HierarchyEdgeDataOpsReal.cpp
  HierarchyEdgeDataOpsReal.h
  HierarchyFaceDataOpsComplex.h
  HierarchyFaceDataOpsInteger.h
  HierarchyFaceDataOpsReal.cpp
  HierarchyFaceDataOpsReal.h
  HierarchyNodeDataOpsComplex.h
  HierarchyNodeDataOpsInteger.h
  HierarchyNodeDataOpsReal.cpp
  HierarchyNodeDataOpsReal.h
  HierarchySideDataOpsComplex.h
  HierarchySideDataOpsInteger.h
  HierarchySideDataOpsReal.cpp
  HierarchySideDataOpsReal.h
  PatchCellDataBasicOps.cpp
  PatchCellDataBasicOps.h
  PatchCellDataMiscellaneousOpsReal.cpp
  PatchCellDataMiscellaneousOpsReal.h
  PatchCellDataNormOpsComplex.h
  PatchCellDataNormOpsReal.cpp
  PatchCellDataNormOpsReal.h
  PatchCellDataOpsComplex.h
  PatchCellDataOpsInteger.h
  PatchCellDataOpsReal.cpp
  PatchCellDataOpsReal.h
  PatchEdgeDataBasicOps.cpp
  PatchEdgeDataBasicOps.h
  PatchEdgeDataMiscellaneousOpsReal.cpp
  PatchEdgeDataMiscellaneousOpsReal.h
  PatchEdgeDataNormOpsComplex.h
  PatchEdgeDataNormOpsReal.cpp
  PatchEdgeDataNormOpsReal.h
  PatchEdgeDataOpsComplex.h
  PatchEdgeDataOpsInteger.h
  PatchEdgeDataOpsReal.cpp
  PatchEdgeDataOpsReal.h
  PatchFaceDataBasicOps.cpp
  PatchFaceDataBasicOps.h
  PatchFaceDataMiscellaneousOpsReal.cpp
  PatchFaceDataMiscellaneousOpsReal.h
  PatchFaceDataNormOpsComplex.h
  PatchFaceDataNormOpsReal.cpp
  PatchFaceDataNormOpsReal.h
  PatchFaceDataOpsComplex.h
  PatchFaceDataOpsInteger.h
  PatchFaceDataOpsReal.cpp
  PatchFaceDataOpsReal.h
  PatchNodeDataBasicOps.cpp
  PatchNodeDataBasicOps.h
  PatchNodeDataMiscellaneousOpsReal.cpp
  PatchNodeDataMiscellaneousOpsReal.h
  PatchNodeDataNormOpsComplex.h
  PatchNodeDataNormOpsReal.cpp
  PatchNodeDataNormOpsReal.h
  PatchNodeDataOpsComplex.h
  PatchNodeDataOpsInteger.h
  PatchNodeDataOpsReal.cpp
  PatchNodeDataOpsReal.h
  PatchSideDataBasicOps.cpp
  PatchSideDataBasicOps.h
  PatchSideDataMiscellaneousOpsReal.cpp
  PatchSideDataMiscellaneousOpsReal.h
  PatchSideDataNormOpsComplex.h
  PatchSideDataNormOpsReal.cpp
  PatchSideDataNormOpsReal.h
  PatchSideDataOpsComplex.h
  PatchSideDataOpsInteger.h
  PatchSideDataOpsReal.cpp
  PatchSideDataOpsReal.h)

set_source_files_properties(
  ArrayDataBasicOps.cpp
  ArrayDataMiscellaneousOpsReal.cpp
  ArrayDataNormOpsReal.cpp
  HierarchyCellDataOpsReal.cpp
  HierarchyDataOpsReal.cpp
  HierarchyEdgeDataOpsReal.cpp
  HierarchyFaceDataOpsReal.cpp
  HierarchyNodeDataOpsReal.cpp
  HierarchySideDataOpsReal.cpp
  PatchCellDataBasicOps.cpp
  PatchCellDataMiscellaneousOpsReal.cpp
  PatchCellDataNormOpsReal.cpp
  PatchCellDataOpsReal.cpp
  PatchEdgeDataBasicOps.cpp
  PatchEdgeDataMiscellaneousOpsReal.cpp
  PatchEdgeDataNormOpsReal.cpp
  PatchEdgeDataOpsReal.cpp
  PatchFaceDataBasicOps.cpp
  PatchFaceDataMiscellaneousOpsReal.cpp
  PatchFaceDataNormOpsReal.cpp
  PatchFaceDataOpsReal.cpp
  PatchNodeDataBasicOps.cpp
  PatchNodeDataMiscellaneousOpsReal.cpp
  PatchNodeDataNormOpsReal.cpp
  PatchNodeDataOpsReal.cpp
  PatchSideDataBasicOps.cpp
  PatchSideDataMiscellaneousOpsReal.cpp
  PatchSideDataNormOpsReal.cpp
  PatchSideDataOpsReal.cpp
  PROPERTIES HEADER_FILE_ONLY True )

set (math_sources
  ArrayDataNormOpsComplex.cpp
  ArrayDataNormOpsInteger.cpp
  HierarchyCellDataOpsComplex.cpp
  HierarchyCellDataOpsInteger.cpp
  HierarchyDataOpsComplex.cpp
  HierarchyDataOpsInteger.cpp
  HierarchyDataOpsManager.cpp
  HierarchyEdgeDataOpsComplex.cpp
  HierarchyEdgeDataOpsInteger.cpp
  HierarchyFaceDataOpsComplex.cpp
  HierarchyFaceDataOpsInteger.cpp
  HierarchyNodeDataOpsComplex.cpp
  HierarchyNodeDataOpsInteger.cpp
  HierarchySideDataOpsComplex.cpp
  HierarchySideDataOpsInteger.cpp
  PatchCellDataNormOpsComplex.cpp
  PatchCellDataOpsComplex.cpp
  PatchCellDataOpsInteger.cpp
  PatchEdgeDataNormOpsComplex.cpp
  PatchEdgeDataOpsComplex.cpp
  PatchEdgeDataOpsInteger.cpp
  PatchFaceDataNormOpsComplex.cpp
  PatchFaceDataOpsComplex.cpp
  PatchFaceDataOpsInteger.cpp
  PatchNodeDataNormOpsComplex.cpp
  PatchNodeDataOpsComplex.cpp
  PatchNodeDataOpsInteger.cpp
  PatchSideDataNormOpsComplex.cpp
  PatchSideDataOpsComplex.cpp
  PatchSideDataOpsInteger.cpp)

set (math_depends
  SAMRAI_hier
  SAMRAI_pdat
  SAMRAI_tbox)

if (ENABLE_CUDA)
  set (math_depends ${math_depends} cuda)
endif ()

if (ENABLE_HIP)
  set (math_depends ${math_depends} blt::hip)
endif ()

blt_add_library(
  NAME SAMRAI_math
  SOURCES ${math_sources}
  HEADERS ${math_headers}
  DEPENDS_ON ${math_depends})

target_include_directories( SAMRAI_math
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>
  $<INSTALL_INTERFACE:include>)

install(TARGETS SAMRAI_math
  EXPORT SAMRAITargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES ${math_headers}
  DESTINATION include/SAMRAI/math)
