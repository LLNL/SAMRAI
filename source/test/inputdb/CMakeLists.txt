set (inputdb_sources
        inputdb.cpp)

set (inputdb_depends SAMRAI_tbox)


if (ENABLE_OPENMP)
  set(inputdb_depends ${inputdb_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(inputdb_depends ${inputdb_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(inputdb_depends ${inputdb_depends} blt::hip)
endif ()


blt_add_executable(
        NAME inputdb
        SOURCES ${inputdb_sources}
        DEPENDS_ON ${inputdb_depends})

target_compile_definitions(
        inputdb
        PRIVATE
        NDIM=2 TESTING=1)

set_target_properties(inputdb PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME inputdb
  EXECUTABLE inputdb
  INPUTS ${test_inputs}
  PARALLEL TRUE)
