
cmake_minimum_required(VERSION 3.28.0 FATAL_ERROR)

project(sat_solver CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
add_library(cnf)
target_sources(cnf
    PUBLIC
        FILE_SET CXX_MODULES FILES
        src/cnf.cpp
)

add_executable(sat_solver main.cpp)
target_link_libraries(sat_solver PRIVATE cnf)

add_executable(test test/tests.cpp)
target_link_libraries(test PUBLIC cnf)
target_link_libraries(test PRIVATE ${GTEST_LIBRARIES} pthread)


# set(TESTS_DIR test)


# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})
# add_executable(run_tests ${TESTS_DIR}/tests.cpp)
# target_link_libraries(run_tests PRIVATE ${GTEST_LIBRARIES} pthread)
# target_compile_options(run_tests PRIVATE "-fsanitize=address")
# target_link_options(run_tests PRIVATE "-fsanitize=address")
