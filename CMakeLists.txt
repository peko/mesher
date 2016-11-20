cmake_minimum_required(VERSION 3.6)

# glfw
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wformat")
file(GLOB src "src/*.h" "src/*.cpp")
file(GLOB imgui "dep/imgui/*.h" "dep/imgui/*.cpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
include_directories(src dep/imgui)
add_executable(shape_mesher ${src} ${imgui})

target_link_libraries(shape_mesher ${GLFW_LIBRARIES} GL)