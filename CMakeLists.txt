
cmake_minimum_required(VERSION 3.28.0 FATAL_ERROR)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

project(sat_solver CXX)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(sat_runtime)
target_sources(sat_runtime
    PUBLIC
        FILE_SET CXX_MODULES FILES
        src/runtime/cnf.cpp
        src/runtime/dpll.cpp
)

add_executable(satr main.cpp)
target_link_libraries(satr PRIVATE sat_runtime)

add_executable(test_runtime test/tests.cpp)
target_link_libraries(test_runtime PUBLIC sat_runtime)
target_link_libraries(test_runtime PRIVATE ${GTEST_LIBRARIES} pthread)


# set(TESTS_DIR test)


# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})
# add_executable(run_tests ${TESTS_DIR}/tests.cpp)
# target_link_libraries(run_tests PRIVATE ${GTEST_LIBRARIES} pthread)
# target_compile_options(run_tests PRIVATE "-fsanitize=address")
# target_link_options(run_tests PRIVATE "-fsanitize=address")
