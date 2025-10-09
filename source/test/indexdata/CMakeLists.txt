set (indexdata_sources
  main.cpp)

set(indexdata_depends ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(indexdata_depends ${indexdata_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(indexdata_depends ${indexdata_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(indexdata_depends ${indexdata_depends} blt::hip)
endif ()

blt_add_executable(
  NAME indexdata
  SOURCES ${indexdata_sources}
  DEPENDS_ON ${indexdata_depends})

target_compile_definitions(indexdata PUBLIC TESTING=1)

set_target_properties(indexdata PROPERTIES LINKER_LANGUAGE CXX)

if(ENABLE_MPI)
  set(TASKS 1)
else()
  set(TASKS 0)
endif()

blt_add_test(
  NAME indexdata
  COMMAND indexdata
  NUM_MPI_TASKS ${TASKS})
