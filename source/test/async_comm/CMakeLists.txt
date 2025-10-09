set (async_depends SAMRAI_tbox)

if (ENABLE_OPENMP)
  set(async_depends ${async_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(async_depends ${async_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(async_depends ${async_depends} blt::hip)
endif ()

blt_add_executable(
  NAME main-async_comm
  SOURCES main-async_comm.cpp
  DEPENDS_ON ${async_depends})

blt_add_executable(
  NAME main-peer_comm
  SOURCES main-peer_comm.cpp
  DEPENDS_ON ${async_depends})

set_target_properties(main-async_comm PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(main-peer_comm PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories( main-async_comm
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/main-async_comm)

target_include_directories( main-peer_comm
  PUBLIC ${PROJECT_SOURCE_DIR}/source/test/main-peer_comm)

target_compile_definitions(main-async_comm PUBLIC TESTING=1)

target_compile_definitions(main-peer_comm PUBLIC TESTING=1)

samrai_add_tests(
  NAME async_comm
  EXECUTABLE main-async_comm
  INPUTS ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/async.default.input
  PARALLEL True)

samrai_add_tests(
  NAME async_comm_peer
  EXECUTABLE main-peer_comm
  INPUTS ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/peer.default.input
  PARALLEL True)
