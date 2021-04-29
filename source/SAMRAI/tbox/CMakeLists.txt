set ( tbox_headers
  AllocatorDatabase.h
  Array.h
  Array.C
  AsyncCommGroup.h
  AsyncCommPeer.h
  AsyncCommPeer.C
  AsyncCommStage.h
  BalancedDepthFirstTree.h
  BreadthFirstRankTree.h
  CenteredRankTree.h
  Clock.h
  Collectives.h
  ConduitDatabase.h
  CommGraphWriter.h
  Complex.h
  Database.h
  DatabaseBox.h
  DatabaseFactory.h
  Dimension.h
  ExecutionPolicy.h
  Grammar.h
  HDFDatabase.h
  HDFDatabaseFactory.h
  IEEE.h
  InputDatabase.h
  InputManager.h
  IOStream.h
  Logger.h
  MathUtilities.h
  MathUtilities.C
  MemoryDatabase.h
  MemoryDatabaseFactory.h
  MemoryUtilities.h
  MessageStream.h
  NullDatabase.h
  NVTXUtilities.h
  OpenMPUtilities.h
  ParallelBuffer.h
  Parser.h
  PIO.h
  RankGroup.h
  RankTreeStrategy.h
  ReferenceCounter.h
  ResourceAllocator.h
  RestartManager.h
  SAMRAI_MPI.h
  SAMRAIManager.h
  Schedule.h
  Serializable.h
  SiloDatabase.h
  SiloDatabaseFactory.h
  StartupShutdownManager.h
  Statistic.h
  Statistician.h
  StatTransaction.h
  Timer.h
  TimerManager.h
  Tracer.h
  Transaction.h
  TransactionFuseable.h
  Utilities.h)

set_source_files_properties(
  Array.C
  MathUtilities.C
  AsyncCommPeer.C
  PROPERTIES HEADER_FILE_ONLY TRUE)

set (tbox_sources
  AllocatorDatabase.C
  ArraySpecial.C
  AsyncCommGroup.C
  AsyncCommStage.C
  BalancedDepthFirstTree.C
  BreadthFirstRankTree.C
  CenteredRankTree.C
  Clock.C
  ConduitDatabase.C
  CommGraphWriter.C
  Database.C
  DatabaseBox.C
  DatabaseFactory.C
  Dimension.C
  Grammar.C
  HDFDatabase.C
  HDFDatabaseFactory.C
  IEEE.C
  InputManager.C
  Logger.C
  MathUtilitiesSpecial.C
  MemoryDatabase.C
  MemoryDatabaseFactory.C
  MemoryUtilities.C
  MessageStream.C
  NullDatabase.C
  PIO.C
  ParallelBuffer.C
  Parser.C
  RankGroup.C
  RankTreeStrategy.C
  ReferenceCounter.C
  RestartManager.C
  SAMRAIManager.C
  SAMRAI_MPI.C
  Scanner.C
  Schedule.C
  Serializable.C
  SiloDatabase.C
  SiloDatabaseFactory.C
  StartupShutdownManager.C
  StatTransaction.C
  Statistic.C
  Statistician.C
  Timer.C
  TimerManager.C
  Tracer.C
  Transaction.C
  TransactionFuseable.C
  Utilities.C)

if (ENABLE_HDF5)
  set(tbox_depends ${tbox_depends} hdf5)
endif ()

if (HAVE_SILO)
  set(tbox_depends ${tbox_depends} silo)
endif ()

if (SAMRAI_HAVE_CONDUIT)
  set(tbox_depends ${tbox_depends} CONDUIT)
endif ()

if (ENABLE_MPI)
  set(tbox_depends ${tbox_depends} mpi)
endif ()

if (ENABLE_UMPIRE)
  set(tbox_depends ${tbox_depends} umpire)
endif ()

if (ENABLE_OPENMP)
  set(tbox_depends ${tbox_depends} openmp)
endif ()

if (ENABLE_RAJA)
  set(tbox_depends ${tbox_depends} raja)
endif ()

if (ENABLE_CUDA)
  set(cuda_sources TransactionFuseable.C Schedule.C)
  set_source_files_properties(${cuda_sources} PROPERTIES LANGUAGE CUDA)

  set (tbox_depends ${tbox_depends} cuda)

  if (ENABLE_NVTX_REGIONS)
    find_package(CUDA REQUIRED)

    find_library(NVTX_LIBRARY
       NAME libnvToolsExt.so
       PATHS ${CUDA_TOOLKIT_ROOT_DIR}/lib64 ${CUDA_TOOLKIT_ROOT_DIR}/lib)

    message(STATUS "NVidia tools extension library found in " ${NVTX_LIBRARY})
    blt_register_library(
     NAME nvToolsExt
     LIBRARIES ${NVTX_LIBRARY})

    set(tbox_depends ${tbox_depends} nvToolsExt)
    message(STATUS "Enable NVTX Regions Detected")
  endif ()
endif ()

blt_add_library( NAME SAMRAI_tbox
  SOURCES ${tbox_sources}
  HEADERS ${tbox_headers}
  DEPENDS_ON ${tbox_depends})

target_include_directories( SAMRAI_tbox
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>
  $<INSTALL_INTERFACE:include>)

blt_print_target_properties(
  TARGET SAMRAI_tbox)


install(TARGETS SAMRAI_tbox
  EXPORT SAMRAITargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES ${tbox_headers}
  DESTINATION include/SAMRAI/tbox)
