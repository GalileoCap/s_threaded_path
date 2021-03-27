cmake_minimum_required(VERSION 3.17)
project(s_threaded_path)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(s_threaded_path main.cpp)
