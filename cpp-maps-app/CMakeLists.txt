cmake_minimum_required(VERSION 3.13.4)
project(cpp_maps_app)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(${cpp_maps_lib_INCLUDE})

add_executable(cpp_maps_app main.cpp)

target_link_libraries(cpp_maps_app
        ${CPP_MAPS_LIBS})
