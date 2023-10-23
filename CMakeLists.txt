
cmake_minimum_required(VERSION 3.28.0 FATAL_ERROR)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)

project(sat_solver CXX)

add_library(sat)
target_sources(sat
    PUBLIC
        FILE_SET CXX_MODULES FILES
        src/sat.cpp
)

add_executable(run main.cpp)
target_link_libraries(run sat)


# set(TESTS_DIR test)


# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})
# add_executable(run_tests ${TESTS_DIR}/tests.cpp)
# target_link_libraries(run_tests PRIVATE ${GTEST_LIBRARIES} pthread)
# target_compile_options(run_tests PRIVATE "-fsanitize=address")
# target_link_options(run_tests PRIVATE "-fsanitize=address")
