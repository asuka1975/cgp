cmake_minimum_required(VERSION 3.16)
project(cgp)

set(CMAKE_CXX_STANDARD 17)
set(CGP_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(GA_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/genetic-algorithm/include)
set(NETWORK_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/network/include)

enable_testing()

add_library(cgp src/cgp.cpp)

target_include_directories(cgp PUBLIC include ${GA_INCLUDE_DIR} ${NETWORK_INCLUDE_DIR})

add_subdirectory(CGP_test)
add_subdirectory(genetic-algorithm)
add_subdirectory(network)