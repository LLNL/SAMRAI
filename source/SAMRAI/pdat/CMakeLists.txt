set (pdat_headers
  ArrayData.C
  ArrayData.h
  ArrayDataAccess.C
  ArrayDataAccess.h
  ArrayDataIterator.h
  ArrayDataOperationUtilities.C
  ArrayDataOperationUtilities.h
  ArrayView.h
  CellConstantRefine.h
  CellComplexConstantRefine.h
  CellComplexLinearTimeInterpolateOp.h
  CellData.C
  CellData.h
  CellDataFactory.C
  CellDataFactory.h
  CellDoubleConstantRefine.h
  CellDoubleLinearTimeInterpolateOp.h
  CellFloatConstantRefine.h
  CellFloatLinearTimeInterpolateOp.h
  CellGeometry.h
  CellIndex.h
  CellIntegerConstantRefine.h
  CellIterator.h
  CellOverlap.h
  CellVariable.C
  CellVariable.h
  CopyOperation.C
  CopyOperation.h
  DoubleAttributeId.h
  EdgeComplexConstantRefine.h
  EdgeComplexLinearTimeInterpolateOp.h
  EdgeData.C
  EdgeData.h
  EdgeDataFactory.C
  EdgeDataFactory.h
  EdgeDoubleConstantRefine.h
  EdgeDoubleLinearTimeInterpolateOp.h
  EdgeFloatConstantRefine.h
  EdgeFloatLinearTimeInterpolateOp.h
  EdgeGeometry.h
  EdgeIndex.h
  EdgeIntegerConstantRefine.h
  EdgeIterator.h
  EdgeOverlap.h
  EdgeVariable.C
  EdgeVariable.h
  FaceComplexConstantRefine.h
  FaceComplexLinearTimeInterpolateOp.h
  FaceData.C
  FaceData.h
  FaceDataFactory.C
  FaceDataFactory.h
  FaceDoubleConstantRefine.h
  FaceDoubleLinearTimeInterpolateOp.h
  FaceFloatConstantRefine.h
  FaceFloatLinearTimeInterpolateOp.h
  FaceGeometry.h
  FaceIndex.h
  FaceIntegerConstantRefine.h
  FaceIterator.h
  FaceOverlap.h
  FaceVariable.C
  FaceVariable.h
  FirstLayerCellNoCornersVariableFillPattern.h
  FirstLayerCellVariableFillPattern.h
  FirstLayerEdgeVariableFillPattern.h
  FirstLayerNodeVariableFillPattern.h
  FirstLayerSideVariableFillPattern.h
  IndexData.C
  IndexData.h
  IndexDataFactory.C
  IndexDataFactory.h
  IndexVariable.C
  IndexVariable.h
  IntegerAttributeId.h
  MDA_Access.h
  NodeComplexInjection.h
  NodeComplexLinearTimeInterpolateOp.h
  NodeData.C
  NodeData.h
  NodeDataFactory.C
  NodeDataFactory.h
  NodeDoubleInjection.h
  NodeDoubleLinearTimeInterpolateOp.h
  NodeFloatInjection.h
  NodeFloatLinearTimeInterpolateOp.h
  NodeGeometry.h
  NodeIndex.h
  NodeIntegerInjection.h
  NodeIterator.h
  NodeOverlap.h
  NodeVariable.C
  NodeVariable.h
  OuteredgeData.C
  OuteredgeData.h
  OuteredgeDataFactory.C
  OuteredgeDataFactory.h
  OuteredgeGeometry.h
  OuteredgeVariable.C
  OuteredgeVariable.h
  OuterfaceComplexConstantRefine.h
  OuterfaceComplexLinearTimeInterpolateOp.h
  OuterfaceData.C
  OuterfaceData.h
  OuterfaceDataFactory.C
  OuterfaceDataFactory.h
  OuterfaceDoubleConstantRefine.h
  OuterfaceDoubleLinearTimeInterpolateOp.h
  OuterfaceFloatConstantRefine.h
  OuterfaceFloatLinearTimeInterpolateOp.h
  OuterfaceGeometry.h
  OuterfaceIntegerConstantRefine.h
  OuterfaceVariable.C
  OuterfaceVariable.h
  OuternodeData.C
  OuternodeData.h
  OuternodeDataFactory.C
  OuternodeDataFactory.h
  OuternodeDoubleInjection.h
  OuternodeGeometry.h
  OuternodeVariable.C
  OuternodeVariable.h
  OutersideComplexLinearTimeInterpolateOp.h
  OutersideData.C
  OutersideData.h
  OutersideDataFactory.C
  OutersideDataFactory.h
  OutersideDoubleLinearTimeInterpolateOp.h
  OutersideFloatLinearTimeInterpolateOp.h
  OutersideGeometry.h
  OutersideVariable.C
  OutersideVariable.h
  SecondLayerNodeNoCornersVariableFillPattern.h
  SecondLayerNodeVariableFillPattern.h
  SideComplexConstantRefine.h
  SideComplexLinearTimeInterpolateOp.h
  SideData.C
  SideData.h
  SideDataFactory.C
  SideDataFactory.h
  SideDoubleConstantRefine.h
  SideDoubleLinearTimeInterpolateOp.h
  SideFloatConstantRefine.h
  SideFloatLinearTimeInterpolateOp.h
  SideGeometry.h
  SideIndex.h
  SideIntegerConstantRefine.h
  SideIterator.h
  SideOverlap.h
  SideVariable.C
  SideVariable.h
  SparseData.C
  SparseData.h
  SparseDataFactory.C
  SparseDataFactory.h
  SparseDataVariable.C
  SparseDataVariable.h
  SumOperation.C
  SumOperation.h)

set_source_files_properties(
  ArrayData.C
  ArrayDataAccess.C
  ArrayDataOperationUtilities.C
  CellData.C
  CellDataFactory.C
  CellVariable.C
  CopyOperation.C
  EdgeData.C
  EdgeDataFactory.C
  EdgeVariable.C
  FaceData.C
  FaceDataFactory.C
  FaceVariable.C
  IndexData.C
  IndexDataFactory.C
  IndexVariable.C
  NodeData.C
  NodeDataFactory.C
  NodeVariable.C
  OuteredgeData.C
  OuteredgeDataFactory.C
  OuteredgeVariable.C
  OuterfaceData.C
  OuterfaceDataFactory.C
  OuterfaceVariable.C
  OuternodeData.C
  OuternodeDataFactory.C
  OuternodeVariable.C
  OutersideData.C
  OutersideDataFactory.C
  OutersideVariable.C
  SideData.C
  SideDataFactory.C
  SideVariable.C
  SparseData.C
  SparseDataFactory.C
  SparseDataVariable.C
  SumOperation.C
  PROPERTIES HEADER_FILE_ONLY TRUE)


set (pdat_sources
  ArrayDataIterator.C
  CellConstantRefine.C
  CellComplexConstantRefine.C
  CellComplexLinearTimeInterpolateOp.C
  CellDoubleConstantRefine.C
  CellDoubleLinearTimeInterpolateOp.C
  CellFloatConstantRefine.C
  CellFloatLinearTimeInterpolateOp.C
  CellGeometry.C
  CellIndex.C
  CellIntegerConstantRefine.C
  CellIterator.C
  CellOverlap.C
  DoubleAttributeId.C
  EdgeComplexConstantRefine.C
  EdgeComplexLinearTimeInterpolateOp.C
  EdgeDoubleConstantRefine.C
  EdgeDoubleLinearTimeInterpolateOp.C
  EdgeFloatConstantRefine.C
  EdgeFloatLinearTimeInterpolateOp.C
  EdgeGeometry.C
  EdgeIndex.C
  EdgeIntegerConstantRefine.C
  EdgeIterator.C
  EdgeOverlap.C
  FaceComplexConstantRefine.C
  FaceComplexLinearTimeInterpolateOp.C
  FaceDoubleConstantRefine.C
  FaceDoubleLinearTimeInterpolateOp.C
  FaceFloatConstantRefine.C
  FaceFloatLinearTimeInterpolateOp.C
  FaceGeometry.C
  FaceIndex.C
  FaceIntegerConstantRefine.C
  FaceIterator.C
  FaceOverlap.C
  FirstLayerCellNoCornersVariableFillPattern.C
  FirstLayerCellVariableFillPattern.C
  FirstLayerEdgeVariableFillPattern.C
  FirstLayerNodeVariableFillPattern.C
  FirstLayerSideVariableFillPattern.C
  IntegerAttributeId.C
  NodeComplexInjection.C
  NodeComplexLinearTimeInterpolateOp.C
  NodeDoubleInjection.C
  NodeDoubleLinearTimeInterpolateOp.C
  NodeFloatInjection.C
  NodeFloatLinearTimeInterpolateOp.C
  NodeGeometry.C
  NodeIndex.C
  NodeIntegerInjection.C
  NodeIterator.C
  NodeOverlap.C
  OuteredgeGeometry.C
  OuterfaceComplexConstantRefine.C
  OuterfaceComplexLinearTimeInterpolateOp.C
  OuterfaceDoubleConstantRefine.C
  OuterfaceDoubleLinearTimeInterpolateOp.C
  OuterfaceFloatConstantRefine.C
  OuterfaceFloatLinearTimeInterpolateOp.C
  OuterfaceGeometry.C
  OuterfaceIntegerConstantRefine.C
  OuternodeDoubleInjection.C
  OuternodeGeometry.C
  OutersideComplexLinearTimeInterpolateOp.C
  OutersideDoubleLinearTimeInterpolateOp.C
  OutersideFloatLinearTimeInterpolateOp.C
  OutersideGeometry.C
  SecondLayerNodeNoCornersVariableFillPattern.C
  SecondLayerNodeVariableFillPattern.C
  SideComplexConstantRefine.C
  SideComplexLinearTimeInterpolateOp.C
  SideDoubleConstantRefine.C
  SideDoubleLinearTimeInterpolateOp.C
  SideFloatConstantRefine.C
  SideFloatLinearTimeInterpolateOp.C
  SideGeometry.C
  SideIndex.C
  SideIntegerConstantRefine.C
  SideIterator.C
  SideOverlap.C
  SparseData.C
  SparseDataFactory.C
  SparseDataVariable.C
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/pdat_concoarsen1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/pdat_concoarsen2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/pdat_concoarsen3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/pdat_conrefine1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/pdat_conrefine2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/pdat_conrefine3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/pdat_dbugfort1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/pdat_dbugfort2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/pdat_dbugfort3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/pdat_lintimint1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/pdat_lintimint2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/pdat_lintimint3d.f)

set (pdat_depends
  SAMRAI_hier
  SAMRAI_tbox
  SAMRAI_xfer)

if (ENABLE_RAJA)
  set(pdat_depends ${pdat_depends} raja)
endif ()

if (ENABLE_CUDA)
  set(pdat_depends ${pdat_depends} cuda)
endif ()

process_m4(NAME fortran/pdat_concoarsen1d)
process_m4(NAME fortran/pdat_concoarsen2d)
process_m4(NAME fortran/pdat_concoarsen3d)
process_m4(NAME fortran/pdat_conrefine1d)
process_m4(NAME fortran/pdat_conrefine2d)
process_m4(NAME fortran/pdat_conrefine3d)
process_m4(NAME fortran/pdat_dbugfort1d)
process_m4(NAME fortran/pdat_dbugfort2d)
process_m4(NAME fortran/pdat_dbugfort3d)
process_m4(NAME fortran/pdat_lintimint1d)
process_m4(NAME fortran/pdat_lintimint2d)
process_m4(NAME fortran/pdat_lintimint3d)

blt_add_library(
  NAME SAMRAI_pdat
  SOURCES ${pdat_sources}
  HEADERS ${pdat_headers}
  DEPENDS_ON ${pdat_depends})

set_target_properties(SAMRAI_pdat PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(
  SAMRAI_pdat
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>
  $<INSTALL_INTERFACE:include>)

blt_print_target_properties(TARGET SAMRAI_pdat)
blt_print_target_properties(TARGET raja)
blt_print_target_properties(TARGET RAJA)

install(TARGETS SAMRAI_pdat
  EXPORT SAMRAITargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES ${pdat_headers}
  DESTINATION include/SAMRAI/pdat)
