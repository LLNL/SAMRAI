set (geom_headers
        CartesianCellConservativeLinearRefine.h
        CartesianCellComplexConservativeLinearRefine.h
        CartesianCellComplexLinearRefine.h
        CartesianCellComplexWeightedAverage.h
        CartesianCellDoubleConservativeLinearRefine.h
        CartesianCellDoubleLinearRefine.h
        CartesianCellDoubleWeightedAverage.h
        CartesianCellFloatConservativeLinearRefine.h
        CartesianCellFloatLinearRefine.h
        CartesianCellFloatWeightedAverage.h
        CartesianEdgeComplexWeightedAverage.h
        CartesianEdgeDoubleConservativeLinearRefine.h
        CartesianEdgeDoubleWeightedAverage.h
        CartesianEdgeFloatConservativeLinearRefine.h
        CartesianEdgeFloatWeightedAverage.h
        CartesianFaceComplexWeightedAverage.h
        CartesianFaceDoubleConservativeLinearRefine.h
        CartesianFaceDoubleWeightedAverage.h
        CartesianFaceFloatConservativeLinearRefine.h
        CartesianFaceFloatWeightedAverage.h
        CartesianGridGeometry.h
        CartesianNodeComplexLinearRefine.h
        CartesianNodeDoubleLinearRefine.h
        CartesianNodeFloatLinearRefine.h
        CartesianOuterfaceComplexWeightedAverage.h
        CartesianOuterfaceDoubleWeightedAverage.h
        CartesianOuterfaceFloatWeightedAverage.h
        CartesianOutersideDoubleWeightedAverage.h
        CartesianPatchGeometry.h
        CartesianSideComplexWeightedAverage.h
        CartesianSideDoubleConservativeLinearRefine.h
        CartesianSideDoubleWeightedAverage.h
        CartesianSideFloatConservativeLinearRefine.h
        CartesianSideFloatWeightedAverage.h
        GridGeometry.h)

set (geom_sources
  CartesianCellConservativeLinearRefine.cpp
  CartesianCellComplexConservativeLinearRefine.cpp
  CartesianCellComplexLinearRefine.cpp
  CartesianCellComplexWeightedAverage.cpp
  CartesianCellDoubleConservativeLinearRefine.cpp
  CartesianCellDoubleLinearRefine.cpp
  CartesianCellDoubleWeightedAverage.cpp
  CartesianCellFloatConservativeLinearRefine.cpp
  CartesianCellFloatLinearRefine.cpp
  CartesianCellFloatWeightedAverage.cpp
  CartesianEdgeComplexWeightedAverage.cpp
  CartesianEdgeDoubleConservativeLinearRefine.cpp
  CartesianEdgeDoubleWeightedAverage.cpp
  CartesianEdgeFloatConservativeLinearRefine.cpp
  CartesianEdgeFloatWeightedAverage.cpp
  CartesianFaceComplexWeightedAverage.cpp
  CartesianFaceDoubleConservativeLinearRefine.cpp
  CartesianFaceDoubleWeightedAverage.cpp
  CartesianFaceFloatConservativeLinearRefine.cpp
  CartesianFaceFloatWeightedAverage.cpp
  CartesianGridGeometry.cpp
  CartesianNodeComplexLinearRefine.cpp
  CartesianNodeDoubleLinearRefine.cpp
  CartesianNodeFloatLinearRefine.cpp
  CartesianOuterfaceComplexWeightedAverage.cpp
  CartesianOuterfaceDoubleWeightedAverage.cpp
  CartesianOuterfaceFloatWeightedAverage.cpp
  CartesianOutersideDoubleWeightedAverage.cpp
  CartesianPatchGeometry.cpp
  CartesianSideComplexWeightedAverage.cpp
  CartesianSideDoubleConservativeLinearRefine.cpp
  CartesianSideDoubleWeightedAverage.cpp
  CartesianSideFloatConservativeLinearRefine.cpp
  CartesianSideFloatWeightedAverage.cpp
  GridGeometry.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/geom_cartcoarsen1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/geom_cartcoarsen2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/geom_cartcoarsen3d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/geom_cartcoarsen4d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/geom_cartrefine1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/geom_cartrefine2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/geom_cartrefine3d.f)

set (geom_depends
  SAMRAI_hier
  SAMRAI_pdat
  SAMRAI_tbox)

if (ENABLE_CUDA)
  set(geom_depends ${geom_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(geom_depends ${geom_depends} blt::hip)
endif ()

process_m4(NAME fortran/geom_cartcoarsen1d)
process_m4(NAME fortran/geom_cartcoarsen2d)
process_m4(NAME fortran/geom_cartcoarsen3d)
process_m4(NAME fortran/geom_cartcoarsen4d)
process_m4(NAME fortran/geom_cartrefine1d)
process_m4(NAME fortran/geom_cartrefine2d)
process_m4(NAME fortran/geom_cartrefine3d)

blt_add_library(
  NAME SAMRAI_geom
  SOURCES ${geom_sources}
  HEADERS ${geom_headers}
  DEPENDS_ON ${geom_depends})

set_target_properties(SAMRAI_geom PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories( SAMRAI_geom
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>
  $<INSTALL_INTERFACE:include>)

install(TARGETS SAMRAI_geom
  EXPORT SAMRAITargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES ${geom_headers}
  DESTINATION include/SAMRAI/geom)
