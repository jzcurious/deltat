cmake_minimum_required(VERSION 3.24...3.30)
project(timeit-lib VERSION 1.0.0 LANGUAGES CXX)

add_library(timeit-lib STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/chronotimer.cpp
)

add_library(timeit ALIAS timeit-lib)

target_include_directories(timeit-lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

message(STATUS ${CMAKE_INSTALL_INCLUDEDIR})
message(STATUS ${CMAKE_CURRENT_LIST_DIR})

target_include_directories(timeit-lib PUBLIC
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)
