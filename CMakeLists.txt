cmake_minimum_required(VERSION 3.24...3.30)
project(deltat LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CUDA_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -O3")

add_subdirectory(deltat)
add_subdirectory(tests)
add_subdirectory(samples)
