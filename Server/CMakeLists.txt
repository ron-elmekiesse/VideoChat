cmake_minimum_required(VERSION 3.10)
project(VideoChat)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")


set(CMAKE_CXX_STANDARD 17)

add_executable(VideoChat /src/server.cpp)