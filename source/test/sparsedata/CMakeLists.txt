set (sparsedata_sources
  main.cpp
  SparseDataTester.cpp)

set(sparsedata_depends
    SAMRAI_tbox
    SAMRAI_hier
    SAMRAI_pdat
    SAMRAI_geom)

if (ENABLE_OPENMP)
  set(sparsedata_depends ${sparsedata_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(sparsedata_depends ${sparsedata_depends} cuda)
endif ()

blt_add_executable(
  NAME main-sparsedata
  SOURCES ${sparsedata_sources}
  DEPENDS_ON ${sparsedata_depends})

target_compile_definitions(main-sparsedata PUBLIC TESTING=1)

set (sparsedataops_sources
  sparse_dataops.cpp)

blt_add_executable(
  NAME sparse
  SOURCES ${sparsedataops_sources}
  DEPENDS_ON ${sparsedata_depends})

target_compile_definitions(sparse PUBLIC TESTING=1)

if(ENABLE_MPI)
  set(TASKS 1)
else()
  set(TASKS 0)
endif()

blt_add_test(
  NAME main-sparsedata
  COMMAND main-sparsedata
  NUM_MPI_TASKS ${TASKS})

blt_add_test(
  NAME sparse
  COMMAND sparse
  NUM_MPI_TASKS ${TASKS})

