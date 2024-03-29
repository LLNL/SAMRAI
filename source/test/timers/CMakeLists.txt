set ( timer_sources
        Foo.cpp
        main_timer.cpp)

set ( stats_sources
        main_stats.cpp)

set ( example_sources
  main_example.cpp)

blt_add_executable(
  NAME timer_timertest
  SOURCES ${timer_sources}
  DEPENDS_ON
    SAMRAI_tbox)

blt_add_executable(
  NAME timer_statstest
  SOURCES ${stats_sources}
  DEPENDS_ON
    SAMRAI_tbox)

blt_add_executable(
  NAME timer_example
  SOURCES ${example_sources}
  DEPENDS_ON
    SAMRAI_tbox)

if(ENABLE_MPI)
  set(TASKS 1)
else()
  set(TASKS 0)
endif()

target_compile_definitions(timer_timertest PUBLIC TESTING=1)
target_compile_definitions(timer_statstest PUBLIC TESTING=1)
target_compile_definitions(timer_example PUBLIC TESTING=1)

file (GLOB test_inputs ${CMAKE_CURRENT_SOURCE_DIR}/test_inputs/*.input)

samrai_add_tests(
  NAME timer_timertest
  EXECUTABLE timer_timertest
  INPUTS ${test_inputs}
  PARALLEL TRUE)

blt_add_test(
  NAME timer_statstest
  COMMAND timer_statstest
  NUM_MPI_TASKS ${TASKS})
