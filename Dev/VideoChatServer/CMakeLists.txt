cmake_minimum_required(VERSION 3.22)
project(VideoChatServer)

set(CMAKE_CXX_STANDARD 17)

set(Boost_ROOT /mnt/c/libs/boost_1_79_0)
set(Boost_INCLUDE_DIR ${Boost_ROOT})
set(Boost_INCLUDE_DIRS ${Boost_ROOT})

find_package(Boost REQUIRED COMPONENTS system)
message(STATUS "** Boost Include: ${Boost_INCLUDE_DIRS}")

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(VideoChatServer src/Main.cpp)
    target_link_libraries(VideoChatServer pthread)
endif()
