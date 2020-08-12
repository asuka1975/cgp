cmake_minimum_required(VERSION 3.16)
project(cgp)

set(CMAKE_CXX_STANDARD 17)

add_library(cgp src/cgp.cpp)

target_include_directories(cgp PUBLIC include)