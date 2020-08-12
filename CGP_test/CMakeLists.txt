cmake_minimum_required(VERSION 3.16)
project(CGP_test)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_executable(CGP_test_run test.cpp)

target_link_libraries(CGP_test_run cgp gtest gmock -pthread)

target_include_directories(CGP_test_run PUBLIC ${CGP_INCLUDE_DIR})