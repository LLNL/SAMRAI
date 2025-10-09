set (defaultlogger_sources
        defaultloggertest.cpp)

set (logger_depends SAMRAI_tbox)

if (ENABLE_OPENMP)
  set(logger_depends ${logger_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(logger_depends ${logger_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(logger_depends ${logger_depends} blt::hip)
endif ()


blt_add_executable(
        NAME defaultlogger
        SOURCES ${defaultlogger_sources}
        DEPENDS_ON ${logger_depends})

set (userlogger_sources
        userloggertest.cpp)

blt_add_executable(
        NAME userlogger
        SOURCES ${userlogger_sources}
        DEPENDS_ON ${logger_depends})

set_target_properties(defaultlogger PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(userlogger PROPERTIES LINKER_LANGUAGE CXX)

if(ENABLE_MPI)
  set(TASKS 1)
else()
  set(TASKS 0)
endif()

blt_add_test(
  NAME defaultlogger
  COMMAND defaultlogger
  NUM_MPI_TASKS ${TASKS})

blt_add_test(
  NAME userlogger
  COMMAND userlogger
  NUM_MPI_TASKS ${TASKS})
