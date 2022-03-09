cmake_minimum_required(VERSION 3.13.4)
project(cpp_maps_lib)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(${PROJECT_NAME}_INCLUDE
        ${CMAKE_SOURCE_DIR}/cpp-maps-lib/include
        CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

include_directories(${${PROJECT_NAME}_INCLUDE})

file(GLOB CPP_MAPS_HEADERS
        "include/*.h"
        )

file(GLOB CPP_MAPS_SOURCE
        "src/*.cpp"
        )

add_library(cpp_maps_lib ${CPP_MAPS_SOURCE} ${CPP_MAPS_HEADERS})

target_link_libraries(cpp_maps_lib)
