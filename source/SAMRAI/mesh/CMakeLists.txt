set (mesh_headers
  BalanceBoxBreaker.h
  BalanceUtilities.h
  BergerRigoutsos.h
  BergerRigoutsosNode.h
  BoxGeneratorStrategy.h
  BoxInTransit.h
  BoxTransitSet.h
  CascadePartitioner.h
  CascadePartitionerTree.h
  ChopAndPackLoadBalancer.h
  GriddingAlgorithm.h
  GriddingAlgorithmConnectorWidthRequestor.h
  GriddingAlgorithmStrategy.h
  LoadBalanceStrategy.h
  MultiblockGriddingTagger.h
  PartitioningParams.h
  SpatialKey.h
  StandardTagAndInitialize.h
  StandardTagAndInitializeConnectorWidthRequestor.h
  StandardTagAndInitStrategy.h
  TagAndInitializeStrategy.h
  TileClustering.h
  TransitLoad.h
  TreeLoadBalancer.h
  VoucherTransitLoad.h)

set (mesh_sources
  BalanceBoxBreaker.cpp
  BalanceUtilities.cpp
  BergerRigoutsos.cpp
  BergerRigoutsosNode.cpp
  BoxGeneratorStrategy.cpp
  BoxTransitSet.cpp
  CascadePartitioner.cpp
  CascadePartitionerTree.cpp
  ChopAndPackLoadBalancer.cpp
  GriddingAlgorithm.cpp
  GriddingAlgorithmConnectorWidthRequestor.cpp
  GriddingAlgorithmStrategy.cpp
  LoadBalanceStrategy.cpp
  MultiblockGriddingTagger.cpp
  PartitioningParams.cpp
  SpatialKey.cpp
  StandardTagAndInitialize.cpp
  StandardTagAndInitializeConnectorWidthRequestor.cpp
  StandardTagAndInitStrategy.cpp
  TagAndInitializeStrategy.cpp
  TileClustering.cpp
  TransitLoad.cpp
  TreeLoadBalancer.cpp
  VoucherTransitLoad.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/mesh_coarsentags1d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/mesh_coarsentags2d.f
  ${CMAKE_CURRENT_BINARY_DIR}/fortran/mesh_coarsentags3d.f)

process_m4(NAME fortran/mesh_coarsentags1d)
process_m4(NAME fortran/mesh_coarsentags2d)
process_m4(NAME fortran/mesh_coarsentags3d)

set (mesh_depends
  SAMRAI_hier
  SAMRAI_tbox
  SAMRAI_xfer)

if (ENABLE_CUDA)
  set (mesh_depends ${mesh_depends} cuda)
endif ()

if (ENABLE_HIP)
  set (mesh_depends ${mesh_depends} blt::hip)
endif ()

blt_add_library(
  NAME SAMRAI_mesh
  SOURCES ${mesh_sources}
  HEADERS ${mesh_headers}
  DEPENDS_ON ${mesh_depends})

set_target_properties(SAMRAI_mesh PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(
  SAMRAI_mesh
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>
  $<INSTALL_INTERFACE:include>)


install(TARGETS SAMRAI_mesh
  EXPORT SAMRAITargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES ${mesh_headers}
  DESTINATION include/SAMRAI/mesh)
