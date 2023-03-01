set ( tbox_headers
  AllocatorDatabase.h
  Array.h
  Array.cpp
  AsyncCommGroup.h
  AsyncCommPeer.h
  AsyncCommPeer.cpp
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
  GPUUtilities.h
  Grammar.h
  HDFDatabase.h
  HDFDatabaseFactory.h
  IEEE.h
  InputDatabase.h
  InputManager.h
  IOStream.h
  KernelFuser.h
  Logger.h
  MathUtilities.h
  MathUtilities.cpp
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
  ScheduleKernelFuser.h
  Serializable.h
  SiloDatabase.h
  SiloDatabaseFactory.h
  StagedKernelFusers.h
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
  Array.cpp
  MathUtilities.cpp
  AsyncCommPeer.cpp
  PROPERTIES HEADER_FILE_ONLY TRUE)

set (tbox_sources
  AllocatorDatabase.cpp
  ArraySpecial.cpp
  AsyncCommGroup.cpp
  AsyncCommStage.cpp
  BalancedDepthFirstTree.cpp
  BreadthFirstRankTree.cpp
  CenteredRankTree.cpp
  Clock.cpp
  ConduitDatabase.cpp
  CommGraphWriter.cpp
  Database.cpp
  DatabaseBox.cpp
  DatabaseFactory.cpp
  Dimension.cpp
  GPUUtilities.cpp
  Grammar.cpp
  HDFDatabase.cpp
  HDFDatabaseFactory.cpp
  IEEE.cpp
  InputManager.cpp
  KernelFuser.cpp
  Logger.cpp
  MathUtilitiesSpecial.cpp
  MemoryDatabase.cpp
  MemoryDatabaseFactory.cpp
  MemoryUtilities.cpp
  MessageStream.cpp
  NullDatabase.cpp
  PIO.cpp
  ParallelBuffer.cpp
  Parser.cpp
  RankGroup.cpp
  RankTreeStrategy.cpp
  ReferenceCounter.cpp
  RestartManager.cpp
  SAMRAIManager.cpp
  SAMRAI_MPI.cpp
  Scanner.cpp
  Schedule.cpp
  ScheduleKernelFuser.cpp
  Serializable.cpp
  SiloDatabase.cpp
  SiloDatabaseFactory.cpp
  StagedKernelFusers.cpp
  StartupShutdownManager.cpp
  StatTransaction.cpp
  Statistic.cpp
  Statistician.cpp
  Timer.cpp
  TimerManager.cpp
  Tracer.cpp
  Transaction.cpp
  TransactionFuseable.cpp
  Utilities.cpp)

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
  set(cuda_sources GPUUtilities.cpp Schedule.cpp TransactionFuseable.cpp)
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
