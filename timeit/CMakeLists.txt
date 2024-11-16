cmake_minimum_required(VERSION 3.24...3.30)
project(timeit-lib VERSION 1.0.0 LANGUAGES CXX)

add_library(timeit STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/chronotimer.cpp
)

target_include_directories(timeit PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
