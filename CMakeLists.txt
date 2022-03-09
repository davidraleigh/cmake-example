cmake_minimum_required(VERSION 3.15)
project(cpp_maps)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cpp-maps-lib)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cpp-maps-app)

set(PROJECT_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/cpp-maps-lib/include)

target_link_libraries(cpp_maps_lib)

enable_testing()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)