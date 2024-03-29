set (testHDF5_sources
  mainHDF5.cpp
  database_tests.cpp)

set (testHDF5AppFileOpen_sources
  mainHDF5AppFileOpen.cpp
  database_tests.cpp)

set (testSilo_sources
  mainSilo.cpp
  database_tests.cpp)

set (testSiloAppFileOpen_sources
  mainSiloAppFileOpen.cpp
  database_tests.cpp)

set (testMemory_sources
  mainMemory.cpp
  database_tests.cpp)

blt_add_executable(
  NAME testHDF5
  SOURCES ${testHDF5_sources}
  DEPENDS_ON
    SAMRAI_hier
    SAMRAI_tbox)

blt_add_executable(
  NAME testHDF5AppFileOpen
  SOURCES ${testHDF5AppFileOpen_sources}
  DEPENDS_ON
    SAMRAI_hier
    SAMRAI_tbox)

blt_add_executable(
  NAME testSilo
  SOURCES ${testSilo_sources}
  DEPENDS_ON
    SAMRAI_hier
    SAMRAI_tbox)

blt_add_executable(
  NAME testSiloAppFileOpen
  SOURCES ${testSiloAppFileOpen_sources}
  DEPENDS_ON
    SAMRAI_hier
    SAMRAI_tbox)

blt_add_executable(
  NAME testMemory
  SOURCES ${testMemory_sources}
  DEPENDS_ON
    SAMRAI_hier
    SAMRAI_tbox)

target_include_directories( testHDF5
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/restartdb)

target_include_directories( testHDF5AppFileOpen
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/restartdb)

target_include_directories( testSilo
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/restartdb)

target_include_directories( testSiloAppFileOpen
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/restartdb)

target_include_directories( testMemory
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/restartdb)

if(ENABLE_MPI)
  set(TASKS 1)
else()
  set(TASKS 0)
endif()

blt_add_test(
  NAME testHDF5
  COMMAND testHDF5
  NUM_MPI_TASKS ${TASKS})

blt_add_test(
  NAME testHDF5AppFileOpen
  COMMAND testHDF5AppFileOpen
  NUM_MPI_TASKS ${TASKS})

blt_add_test(
  NAME testSilo
  COMMAND testSilo
  NUM_MPI_TASKS ${TASKS})

blt_add_test(
  NAME testSiloAppFileOpen
  COMMAND testSiloAppFileOpen
  NUM_MPI_TASKS ${TASKS})

blt_add_test(
  NAME testMemory
  COMMAND testMemory
  NUM_MPI_TASKS ${TASKS})
