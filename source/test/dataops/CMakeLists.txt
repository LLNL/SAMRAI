set (indx_dataops_sources
  indx_dataops.cpp
  SampleIndexData.cpp)

set(dataops_depends ${SAMRAI_LIBRARIES})

# TODO CMake should resolve this dependency for us...
if (ENABLE_OPENMP)
  set(dataops_depends ${dataops_depends} openmp)
endif ()

if (ENABLE_CUDA)
  set(dataops_depends ${dataops_depends} cuda)
endif ()

if (ENABLE_HIP)
  set(dataops_depends ${dataops_depends} blt::hip)
endif ()

blt_add_executable(
  NAME indx_dataops
  SOURCES ${indx_dataops_sources}
  DEPENDS_ON
    ${dataops_depends})


blt_add_executable(
  NAME cell_fillall
  SOURCES cell_fillall.cpp
  DEPENDS_ON
    ${dataops_depends})

blt_add_executable(
  NAME cell_patchtest
  SOURCES cell_patchtest.cpp
  DEPENDS_ON
    ${dataops_depends})


blt_add_executable(
  NAME cell_hiertest
  SOURCES cell_hiertest.cpp
  DEPENDS_ON
    ${dataops_depends})


blt_add_executable(
  NAME cell_hiertest3d
  SOURCES cell_hiertest.cpp
  DEPENDS_ON
    ${dataops_depends})


blt_add_executable(
  NAME edge_hiertest
  SOURCES edge_hiertest.cpp
  DEPENDS_ON
    ${dataops_depends})


blt_add_executable(
  NAME face_hiertest
  SOURCES face_hiertest.cpp
  DEPENDS_ON
    ${dataops_depends})


blt_add_executable(
  NAME side_hiertest
  SOURCES side_hiertest.cpp
  DEPENDS_ON
    ${dataops_depends})


blt_add_executable(
  NAME node_hiertest
  SOURCES node_hiertest.cpp
  DEPENDS_ON
    ${dataops_depends})


blt_add_executable(
  NAME cell_cplxtest
  SOURCES cell_cplxtest.cpp
  DEPENDS_ON
    ${dataops_depends})


blt_add_executable(
  NAME edge_cplxtest
  SOURCES edge_cplxtest.cpp
  DEPENDS_ON
    ${dataops_depends})


blt_add_executable(
  NAME node_cplxtest
  SOURCES node_cplxtest.cpp
  DEPENDS_ON
    ${dataops_depends})


blt_add_executable(
  NAME face_cplxtest
  SOURCES face_cplxtest.cpp
  DEPENDS_ON
    ${dataops_depends})


blt_add_executable(
  NAME side_cplxtest
  SOURCES side_cplxtest.cpp
  DEPENDS_ON
    ${dataops_depends})


set_target_properties(indx_dataops PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(cell_fillall PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(cell_patchtest PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(cell_hiertest PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(cell_hiertest3d PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(edge_hiertest PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(face_hiertest PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(side_hiertest PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(node_hiertest PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(cell_cplxtest PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(edge_cplxtest PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(node_cplxtest PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(face_cplxtest PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(side_cplxtest PROPERTIES LINKER_LANGUAGE CXX)

target_compile_definitions(indx_dataops PUBLIC DISPLAY TESTING=1)
target_compile_definitions(cell_patchtest PUBLIC DISPLAY TESTING=1)
target_compile_definitions(cell_hiertest PUBLIC DISPLAY TESTING=1)
target_compile_definitions(cell_hiertest3d PUBLIC DISPLAY TESTING=1)
target_compile_definitions(edge_hiertest PUBLIC DISPLAY TESTING=1)
target_compile_definitions(face_hiertest PUBLIC DISPLAY TESTING=1)
target_compile_definitions(side_hiertest PUBLIC DISPLAY TESTING=1)
target_compile_definitions(node_hiertest PUBLIC DISPLAY TESTING=1)
target_compile_definitions(cell_cplxtest PUBLIC DISPLAY TESTING=1)
target_compile_definitions(edge_cplxtest PUBLIC DISPLAY TESTING=1)
target_compile_definitions(node_cplxtest PUBLIC DISPLAY TESTING=1)
target_compile_definitions(face_cplxtest PUBLIC DISPLAY TESTING=1)
target_compile_definitions(side_cplxtest PUBLIC DISPLAY TESTING=1)

target_include_directories(indx_dataops PUBLIC ${PROJECT_SOURCE_DIR}/source/test/dataops)
target_include_directories(cell_patchtest PUBLIC ${PROJECT_SOURCE_DIR}/source/test/dataops)
target_include_directories(cell_hiertest PUBLIC ${PROJECT_SOURCE_DIR}/source/test/dataops)
target_include_directories(cell_hiertest3d PUBLIC ${PROJECT_SOURCE_DIR}/source/test/dataops)
target_include_directories(edge_hiertest PUBLIC ${PROJECT_SOURCE_DIR}/source/test/dataops)
target_include_directories(face_hiertest PUBLIC ${PROJECT_SOURCE_DIR}/source/test/dataops)
target_include_directories(side_hiertest PUBLIC ${PROJECT_SOURCE_DIR}/source/test/dataops)
target_include_directories(node_hiertest PUBLIC ${PROJECT_SOURCE_DIR}/source/test/dataops)
target_include_directories(cell_cplxtest PUBLIC ${PROJECT_SOURCE_DIR}/source/test/dataops)
target_include_directories(edge_cplxtest PUBLIC ${PROJECT_SOURCE_DIR}/source/test/dataops)
target_include_directories(node_cplxtest PUBLIC ${PROJECT_SOURCE_DIR}/source/test/dataops)
target_include_directories(face_cplxtest PUBLIC ${PROJECT_SOURCE_DIR}/source/test/dataops)
target_include_directories(side_cplxtest PUBLIC ${PROJECT_SOURCE_DIR}/source/test/dataops)

if(ENABLE_MPI)
  set(TASKS 1)
else()
  set(TASKS 0)
endif()

foreach(dim RANGE 2 ${MAXDIM})
  blt_add_test(
    NAME indx_dataops${dim}
    COMMAND indx_dataops ${dim}
    NUM_MPI_TASKS ${TASKS})

  blt_add_test(
    NAME cell_patchtest${dim}
    COMMAND cell_patchtest ${dim}
    NUM_MPI_TASKS ${TASKS})

  blt_add_test(
    NAME cell_hiertest${dim}
    COMMAND cell_hiertest ${dim}
    NUM_MPI_TASKS ${TASKS})

  blt_add_test(
    NAME cell_hiertest3d${dim}
    COMMAND cell_hiertest3d ${dim}
    NUM_MPI_TASKS ${TASKS})

  blt_add_test(
    NAME edge_hiertest${dim}
    COMMAND edge_hiertest ${dim}
    NUM_MPI_TASKS ${TASKS})

  blt_add_test(
    NAME face_hiertest${dim}
    COMMAND face_hiertest ${dim}
    NUM_MPI_TASKS ${TASKS})

  blt_add_test(
    NAME side_hiertest${dim}
    COMMAND side_hiertest ${dim}
    NUM_MPI_TASKS ${TASKS})

  blt_add_test(
    NAME node_hiertest${dim}
    COMMAND node_hiertest ${dim}
    NUM_MPI_TASKS ${TASKS})

  blt_add_test(
    NAME cell_cplxtest${dim}
    COMMAND cell_cplxtest ${dim}
    NUM_MPI_TASKS ${TASKS})

  blt_add_test(
    NAME edge_cplxtest${dim}
    COMMAND edge_cplxtest ${dim}
    NUM_MPI_TASKS ${TASKS})

  blt_add_test(
    NAME node_cplxtest${dim}
    COMMAND node_cplxtest ${dim}
    NUM_MPI_TASKS ${TASKS})

  blt_add_test(
    NAME face_cplxtest${dim}
    COMMAND face_cplxtest ${dim}
    NUM_MPI_TASKS ${TASKS})

  blt_add_test(
    NAME side_cplxtest${dim}
    COMMAND side_cplxtest ${dim}
    NUM_MPI_TASKS ${TASKS})
endforeach(dim)
