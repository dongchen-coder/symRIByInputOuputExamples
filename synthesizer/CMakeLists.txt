cmake_minimum_required(VERSION 3.10)
project(synthesizer)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O2 -pipe")

add_subdirectory(src)
add_subdirectory(lib)

