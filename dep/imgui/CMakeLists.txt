cmake_minimum_required(VERSION 3.6)
project(shape_mesher)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB sources "*.h" "*.cpp")
add_library(imgui ${sources})

target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
