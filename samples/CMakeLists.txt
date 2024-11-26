cmake_minimum_required(VERSION 3.24...3.30)
project(timeit-sample LANGUAGES CXX)

add_executable(timeit-sample
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sample.cpp
)

target_link_libraries(timeit-sample PRIVATE
    timeit
)
