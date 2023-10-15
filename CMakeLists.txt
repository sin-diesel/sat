
cmake_minimum_required(VERSION 3.23.0)

project(sat_solver)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
add_executable(project_name main.cpp)
set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(run_tests tests.cpp)
target_link_libraries(run_tests PRIVATE ${GTEST_LIBRARIES} pthread)
target_compile_options(run_tests PRIVATE "-fsanitize=address")
target_link_options(run_tests PRIVATE "-fsanitize=address")
