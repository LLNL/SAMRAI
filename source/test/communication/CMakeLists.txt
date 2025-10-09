set ( communication_sources
  main.cpp
  CommTester.cpp
  PatchDataTestStrategy.cpp
  CellDataTest.cpp
  EdgeDataTest.cpp
  FaceDataTest.cpp
  NodeDataTest.cpp
  OuterfaceDataTest.cpp
  OuternodeDataTest.cpp
  OutersideDataTest.cpp
  SideDataTest.cpp)

set(communication_depends ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(communication_depends ${communication_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(communication_depends ${communication_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(communication_depends ${communication_depends} blt::hip)
endif ()

set(communication_depends ${communication_depends} testlib)


blt_add_executable(
  NAME communication
  SOURCES ${communication_sources}
  DEPENDS_ON ${communication_depends})

target_include_directories( communication
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/communication)

target_compile_definitions(communication PUBLIC TESTING=1)

set_target_properties(communication PROPERTIES LINKER_LANGUAGE CXX)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME communication
  EXECUTABLE communication
  INPUTS ${test_inputs}
  PARALLEL TRUE)
