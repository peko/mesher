cmake_minimum_required(VERSION 3.6)

project(shape_mesher)

find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wformat")
file(GLOB sources "*.h" "*.cpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
add_executable(shape_mesher ${sources})
target_link_libraries(shape_mesher LINK_PUBLIC imgui ${GLFW_LIBRARIES} GL)