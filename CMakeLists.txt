cmake_minimum_required(VERSION 3.16)
project(cgp)

set(CMAKE_CXX_STANDARD 17)
set(CGP_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

enable_testing()

add_library(cgp src/cgp.cpp)

target_include_directories(cgp PUBLIC include)

add_subdirectory(CGP_test)