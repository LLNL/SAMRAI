set (mapped_box_sources
        main-iterators.cpp)

set (mapped_box_depends SAMRAI_hier SAMRAI_tbox)

if (ENABLE_OPENMP)
  set(mapped_box_depends ${mapped_box_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(mapped_box_depends ${mapped_box_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(mapped_box_depends ${mapped_box_depends} blt::hip)
endif ()

blt_add_executable(
        NAME mapped_box_set_iterators
        SOURCES ${mapped_box_sources}
        DEPENDS_ON ${mapped_box_depends})

set_target_properties(mapped_box_set_iterators PROPERTIES LINKER_LANGUAGE CXX)

if(ENABLE_MPI)
  set(TASKS 1)
else()
  set(TASKS 0)
endif()

blt_add_test(
  NAME mapped_box_set_iterators
  COMMAND mapped_box_set_iterators
  NUM_MPI_TASKS ${TASKS})
