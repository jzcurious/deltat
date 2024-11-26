cmake_minimum_required(VERSION 3.24...3.30)
project(deltat-sample LANGUAGES CXX)

add_executable(deltat-sample
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sample.cpp
)

target_link_libraries(deltat-sample PRIVATE
    deltat
)
