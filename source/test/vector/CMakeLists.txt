if(ENABLE_MPI)
  set(TASKS 1)
else()
  set(TASKS 0)
endif()

set(vector_depends ${SAMRAI_LIBRARIES})

if (ENABLE_OPENMP)
  set(vector_depends ${vector_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(vector_depends ${vector_depends} cuda) 
endif ()

if (ENABLE_HIP)
  set(vector_depends ${vector_depends} blt::hip) 
endif ()

blt_add_executable(
  NAME kvtest
  SOURCES kvtest.cpp
  DEPENDS_ON ${vector_depends})

blt_add_executable(
  NAME pvtest
  SOURCES pvtest.cpp
  DEPENDS_ON ${vector_depends})

set_target_properties(kvtest PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(pvtest PROPERTIES LINKER_LANGUAGE CXX)

blt_add_test(
  NAME kvtest
  COMMAND kvtest
  NUM_MPI_TASKS ${TASKS})

blt_add_test(
  NAME pvtest
  COMMAND pvtest
  NUM_MPI_TASKS ${TASKS})

