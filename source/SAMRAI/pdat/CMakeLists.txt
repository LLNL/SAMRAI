set (pdat_headers
  ArrayData.cpp
  ArrayData.h
  ArrayDataAccess.cpp
  ArrayDataAccess.h
  ArrayDataIterator.h
  ArrayDataOperationUtilities.cpp
  ArrayDataOperationUtilities.h
  ArrayView.h
  CellConstantRefine.h
  CellComplexConstantRefine.h
  CellComplexLinearTimeInterpolateOp.h
  CellData.cpp
  CellData.h
  CellDataFactory.cpp
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
  CellVariable.cpp
  CellVariable.h
  CopyOperation.cpp
  CopyOperation.h
  DoubleAttributeId.h
  EdgeComplexConstantRefine.h
  EdgeComplexLinearTimeInterpolateOp.h
  EdgeData.cpp
  EdgeData.h
  EdgeDataFactory.cpp
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
  EdgeVariable.cpp
  EdgeVariable.h
  FaceComplexConstantRefine.h
  FaceComplexLinearTimeInterpolateOp.h
  FaceData.cpp
  FaceData.h
  FaceDataFactory.cpp
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
  FaceVariable.cpp
  FaceVariable.h
  FirstLayerCellNoCornersVariableFillPattern.h
  FirstLayerCellVariableFillPattern.h
  FirstLayerEdgeVariableFillPattern.h
  FirstLayerNodeVariableFillPattern.h
  FirstLayerSideVariableFillPattern.h
  IndexData.cpp
  IndexData.h
  IndexDataFactory.cpp
  IndexDataFactory.h
  IndexVariable.cpp
  IndexVariable.h
  IntegerAttributeId.h
  MDA_Access.h
  NodeComplexInjection.h
  NodeComplexLinearTimeInterpolateOp.h
  NodeData.cpp
  NodeData.h
  NodeDataFactory.cpp
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
  NodeVariable.cpp
  NodeVariable.h
  OuteredgeData.cpp
  OuteredgeData.h
  OuteredgeDataFactory.cpp
  OuteredgeDataFactory.h
  OuteredgeGeometry.h
  OuteredgeVariable.cpp
  OuteredgeVariable.h
  OuterfaceComplexConstantRefine.h
  OuterfaceComplexLinearTimeInterpolateOp.h
  OuterfaceData.cpp
  OuterfaceData.h
  OuterfaceDataFactory.cpp
  OuterfaceDataFactory.h
  OuterfaceDoubleConstantRefine.h
  OuterfaceDoubleLinearTimeInterpolateOp.h
  OuterfaceFloatConstantRefine.h
  OuterfaceFloatLinearTimeInterpolateOp.h
  OuterfaceGeometry.h
  OuterfaceIntegerConstantRefine.h
  OuterfaceVariable.cpp
  OuterfaceVariable.h
  OuternodeData.cpp
  OuternodeData.h
  OuternodeDataFactory.cpp
  OuternodeDataFactory.h
  OuternodeDoubleInjection.h
  OuternodeGeometry.h
  OuternodeVariable.cpp
  OuternodeVariable.h
  OutersideComplexLinearTimeInterpolateOp.h
  OutersideData.cpp
  OutersideData.h
  OutersideDataFactory.cpp
  OutersideDataFactory.h
  OutersideDoubleLinearTimeInterpolateOp.h
  OutersideFloatLinearTimeInterpolateOp.h
  OutersideGeometry.h
  OutersideVariable.cpp
  OutersideVariable.h
  SecondLayerNodeNoCornersVariableFillPattern.h
  SecondLayerNodeVariableFillPattern.h
  SideComplexConstantRefine.h
  SideComplexLinearTimeInterpolateOp.h
  SideData.cpp
  SideData.h
  SideDataFactory.cpp
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
  SideVariable.cpp
  SideVariable.h
  SparseData.cpp
  SparseData.h
  SparseDataFactory.cpp
  SparseDataFactory.h
  SparseDataVariable.cpp
  SparseDataVariable.h
  SumOperation.cpp
  SumOperation.h)

set_source_files_properties(
  ArrayData.cpp
  ArrayDataAccess.cpp
  ArrayDataOperationUtilities.cpp
  CellData.cpp
  CellDataFactory.cpp
  CellVariable.cpp
  CopyOperation.cpp
  EdgeData.cpp
  EdgeDataFactory.cpp
  EdgeVariable.cpp
  FaceData.cpp
  FaceDataFactory.cpp
  FaceVariable.cpp
  IndexData.cpp
  IndexDataFactory.cpp
  IndexVariable.cpp
  NodeData.cpp
  NodeDataFactory.cpp
  NodeVariable.cpp
  OuteredgeData.cpp
  OuteredgeDataFactory.cpp
  OuteredgeVariable.cpp
  OuterfaceData.cpp
  OuterfaceDataFactory.cpp
  OuterfaceVariable.cpp
  OuternodeData.cpp
  OuternodeDataFactory.cpp
  OuternodeVariable.cpp
  OutersideData.cpp
  OutersideDataFactory.cpp
  OutersideVariable.cpp
  SideData.cpp
  SideDataFactory.cpp
  SideVariable.cpp
  SparseData.cpp
  SparseDataFactory.cpp
  SparseDataVariable.cpp
  SumOperation.cpp
  PROPERTIES HEADER_FILE_ONLY TRUE)


set (pdat_sources
  ArrayDataIterator.cpp
  CellConstantRefine.cpp
  CellComplexConstantRefine.cpp
  CellComplexLinearTimeInterpolateOp.cpp
  CellDoubleConstantRefine.cpp
  CellDoubleLinearTimeInterpolateOp.cpp
  CellFloatConstantRefine.cpp
  CellFloatLinearTimeInterpolateOp.cpp
  CellGeometry.cpp
  CellIndex.cpp
  CellIntegerConstantRefine.cpp
  CellIterator.cpp
  CellOverlap.cpp
  DoubleAttributeId.cpp
  EdgeComplexConstantRefine.cpp
  EdgeComplexLinearTimeInterpolateOp.cpp
  EdgeDoubleConstantRefine.cpp
  EdgeDoubleLinearTimeInterpolateOp.cpp
  EdgeFloatConstantRefine.cpp
  EdgeFloatLinearTimeInterpolateOp.cpp
  EdgeGeometry.cpp
  EdgeIndex.cpp
  EdgeIntegerConstantRefine.cpp
  EdgeIterator.cpp
  EdgeOverlap.cpp
  FaceComplexConstantRefine.cpp
  FaceComplexLinearTimeInterpolateOp.cpp
  FaceDoubleConstantRefine.cpp
  FaceDoubleLinearTimeInterpolateOp.cpp
  FaceFloatConstantRefine.cpp
  FaceFloatLinearTimeInterpolateOp.cpp
  FaceGeometry.cpp
  FaceIndex.cpp
  FaceIntegerConstantRefine.cpp
  FaceIterator.cpp
  FaceOverlap.cpp
  FirstLayerCellNoCornersVariableFillPattern.cpp
  FirstLayerCellVariableFillPattern.cpp
  FirstLayerEdgeVariableFillPattern.cpp
  FirstLayerNodeVariableFillPattern.cpp
  FirstLayerSideVariableFillPattern.cpp
  IntegerAttributeId.cpp
  NodeComplexInjection.cpp
  NodeComplexLinearTimeInterpolateOp.cpp
  NodeDoubleInjection.cpp
  NodeDoubleLinearTimeInterpolateOp.cpp
  NodeFloatInjection.cpp
  NodeFloatLinearTimeInterpolateOp.cpp
  NodeGeometry.cpp
  NodeIndex.cpp
  NodeIntegerInjection.cpp
  NodeIterator.cpp
  NodeOverlap.cpp
  OuteredgeGeometry.cpp
  OuterfaceComplexConstantRefine.cpp
  OuterfaceComplexLinearTimeInterpolateOp.cpp
  OuterfaceDoubleConstantRefine.cpp
  OuterfaceDoubleLinearTimeInterpolateOp.cpp
  OuterfaceFloatConstantRefine.cpp
  OuterfaceFloatLinearTimeInterpolateOp.cpp
  OuterfaceGeometry.cpp
  OuterfaceIntegerConstantRefine.cpp
  OuternodeDoubleInjection.cpp
  OuternodeGeometry.cpp
  OutersideComplexLinearTimeInterpolateOp.cpp
  OutersideDoubleLinearTimeInterpolateOp.cpp
  OutersideFloatLinearTimeInterpolateOp.cpp
  OutersideGeometry.cpp
  SecondLayerNodeNoCornersVariableFillPattern.cpp
  SecondLayerNodeVariableFillPattern.cpp
  SideComplexConstantRefine.cpp
  SideComplexLinearTimeInterpolateOp.cpp
  SideDoubleConstantRefine.cpp
  SideDoubleLinearTimeInterpolateOp.cpp
  SideFloatConstantRefine.cpp
  SideFloatLinearTimeInterpolateOp.cpp
  SideGeometry.cpp
  SideIndex.cpp
  SideIntegerConstantRefine.cpp
  SideIterator.cpp
  SideOverlap.cpp
  SparseData.cpp
  SparseDataFactory.cpp
  SparseDataVariable.cpp
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

install(FILES
  fortran/pdat_m4arrdim1d.i
  fortran/pdat_m4arrdim2d.i
  fortran/pdat_m4arrdim3d.i
  fortran/pdat_m4arrdim4d.i
  DESTINATION include/SAMRAI/pdat/fortran)
