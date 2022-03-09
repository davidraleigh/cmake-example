# https://github.com/dmonopoly/gtest-cmake-example/blob/master/CMakeLists.txt
# http://www.kaizou.org/2014/11/gtest-cmake/
# https://stackoverflow.com/questions/8507723/how-to-start-working-with-gtest-and-cmake
cmake_minimum_required(VERSION 3.7)

project(unitTest C CXX)
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS}
        ${cpp_maps_lib_INCLUDE}
        ${CMAKE_SOURCE_DIR}/cpp-maps-lib/include)

set(SOURCE_FILES ./main.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(unitTest ${SOURCE_FILES})

target_link_libraries(unitTest
        ${CPP_MAPS_LIBS}
        ${GTEST_BOTH_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT})

