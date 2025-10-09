set (transformation_depends SAMRAI_pdat SAMRAI_hier SAMRAI_tbox)

if (ENABLE_OPENMP)
  set(transformation_depends ${transformation_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(transformation_depends ${transformation_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(transformation_depends ${transformation_depends} blt::hip)
endif ()


blt_add_executable(
  NAME transformation
  SOURCES main.cpp
  DEPENDS_ON ${transformation_depends})

target_include_directories( transformation
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/transformation)

set_target_properties(transformation PROPERTIES LINKER_LANGUAGE CXX)

if(ENABLE_MPI)
  set(TASKS 1)
else()
  set(TASKS 0)
endif()

blt_add_test(
  NAME transformation
  COMMAND transformation
  NUM_MPI_TASKS ${TASKS})
