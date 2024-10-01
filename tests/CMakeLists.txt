cmake_minimum_required(VERSION 3.24...3.30)
project(timeit-tests VERSION 1.0.0 LANGUAGES CXX)

include(GoogleTest)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)

FetchContent_MakeAvailable(googletest)

add_executable(timeit-tests
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tests.cpp
)

target_include_directories(timeit-tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../timeit/include
)

target_link_libraries(timeit-tests PRIVATE
    timeit
    GTest::gtest_main
)

enable_testing()
gtest_discover_tests(timeit-tests)
