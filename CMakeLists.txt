cmake_minimum_required(VERSION 3.12)
project(Fe)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Fe src/Signal.cpp src/Simulator.cpp)
# add_executable(Fe src/Signal.cpp src/Simulator.cpp)