set ( time_interp_sources
  main.cpp
)

set(time_interp_depends ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(time_interp_depends ${time_interp_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(time_interp_depends ${time_interp_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(time_interp_depends ${time_interp_depends} blt::hip)
endif ()

set(time_interp_depends ${time_interp_depends} testlib)



blt_add_executable(
  NAME time_interp
  SOURCES ${time_interp_sources}
  DEPENDS_ON ${time_interp_depends})

# original library depends
#    SAMRAI_tbox
#    SAMRAI_hier
#    SAMRAI_pdat)

target_include_directories( time_interp
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/time_interp)

target_compile_definitions(time_interp PUBLIC TESTING=1)

set_target_properties(time_interp PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME time_interp
  EXECUTABLE time_interp
  INPUTS ${test_inputs}
  PARALLEL FALSE)
