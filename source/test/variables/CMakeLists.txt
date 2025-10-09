
set(variables_depends ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(variables_depends ${variables_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(variables_depends ${variables_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(variables_depends ${variables_depends} blt::hip)
endif ()

blt_add_executable(NAME variables
  SOURCES main-var_db.cpp
  DEPENDS_ON ${variables_depends})

target_compile_definitions(variables PUBLIC TESTING=1)

set_target_properties(variables PROPERTIES LINKER_LANGUAGE CXX)

if(ENABLE_MPI)
  set(TASKS 1)
else()
  set(TASKS 0)
endif()

blt_add_test(
  NAME variables
  COMMAND variables
  NUM_MPI_TASKS ${TASKS})
