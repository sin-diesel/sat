
cmake_minimum_required(VERSION 3.28.0 FATAL_ERROR)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --stdlib libc++ -lc++abi")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

project(sat_solver CXX)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
add_library(sat)
target_sources(sat
    PUBLIC
        FILE_SET CXX_MODULES FILES
        src/cnf.cpp
        src/dpll.cpp
)

add_executable(sat_solver main.cpp)
target_link_libraries(sat_solver PRIVATE sat)

add_executable(test test/tests.cpp)
target_link_libraries(test PUBLIC sat)
target_link_libraries(test PRIVATE ${GTEST_LIBRARIES} pthread)


# set(TESTS_DIR test)


# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})
# add_executable(run_tests ${TESTS_DIR}/tests.cpp)
# target_link_libraries(run_tests PRIVATE ${GTEST_LIBRARIES} pthread)
# target_compile_options(run_tests PRIVATE "-fsanitize=address")
# target_link_options(run_tests PRIVATE "-fsanitize=address")
