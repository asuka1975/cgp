cmake_minimum_required(VERSION 3.16)
project(cgp)

set(CMAKE_CXX_STANDARD 17)
set(CGP_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(GA_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/genetic-algorithm/include)
set(NETWORK_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/network/include)

enable_testing()

add_library(cgp src/cgp.cpp src/cgp_genome.cpp)

target_include_directories(cgp PUBLIC include ${GA_INCLUDE_DIR} ${NETWORK_INCLUDE_DIR})

if(NOT TARGET CGP_test)
    add_subdirectory(CGP_test)
endif()
if(NOT TARGET genetic-algorithm)
    add_subdirectory(genetic-algorithm)
endif()
if(NOT TARGET network)
    add_subdirectory(network)
endif()