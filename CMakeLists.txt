cmake_minimum_required(VERSION 3.6)

# dependencies
# glfw
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

#cgal
find_package(CGAL QUIET COMPONENTS )
if ( NOT CGAL_FOUND )
    message(STATUS "This project requires the CGAL library, and will not be compiled.")
    return()
endif()
# include helper file
include( ${CGAL_USE_FILE} )
# Boost and its components
find_package( Boost REQUIRED )
if ( NOT Boost_FOUND )
    message(STATUS "This project requires the Boost library, and will not be compiled.")
    return()
endif()

# flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wformat")
#set(CMAKE_BUILD_TYPE "Debug")

# shapelib
add_subdirectory(dep/shapelib-1.3.0)

# source files
file(GLOB src "src/*.h" "src/*.cpp")
file(GLOB imgui "dep/imgui/*.h" "dep/imgui/*.cpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

# includes
include_directories(src dep/imgui dep/shapelib-1.3.0)

# shape_mesher
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_executable(shape_mesher ${src} ${imgui})
target_link_libraries(
        shape_mesher
        ${GLFW_LIBRARIES}
        ${CGAL_LIBRARIES}
        ${CGAL_3RD_PARTY_LIBRARIES}
        GL shapelib)

#add_executable( test_cgal  test_cgal.cpp )
#add_to_cached_list( CGAL_EXECUTABLE_TARGETS test_cgal )
# Link the executable to CGAL and third-party libraries
#target_link_libraries(test_cgal   ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES} )

