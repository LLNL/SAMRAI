set (simple_sources
  main.cpp)

set(simple_depends ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(simple_depends ${simple_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(simple_depends ${simple_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(simple_depends ${simple_depends} blt::hip)
endif ()

blt_add_executable(
  NAME simple
  SOURCES ${simple_sources}
  DEPENDS_ON ${simple_depends})

target_include_directories( simple
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/applications/Simple)

set_target_properties(simple PROPERTIES LINKER_LANGUAGE CXX)



