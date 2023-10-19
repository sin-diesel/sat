
cmake_minimum_required(VERSION 3.27.0 FATAL_ERROR)


set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API aa1f7df0-828a-4fcd-9afc-2dc80491aca7)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

project(sat_solver CXX)

add_executable(sats)
target_sources(sats
    PUBLIC
    main.cpp
)
target_sources(sats
    PUBLIC
        FILE_SET cpp_modules TYPE CXX_MODULES FILES
        src/sat.cppm
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT sats)

# set(TESTS_DIR test)


# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})
# add_executable(run_tests ${TESTS_DIR}/tests.cpp)
# target_link_libraries(run_tests PRIVATE ${GTEST_LIBRARIES} pthread)
# target_compile_options(run_tests PRIVATE "-fsanitize=address")
# target_link_options(run_tests PRIVATE "-fsanitize=address")
