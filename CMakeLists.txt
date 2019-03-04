cmake_minimum_required(VERSION 3.12)
project(Fe)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(Fe src/Main.cpp src/Console.cpp)# src/Signal.cpp src/Simulator.cpp)

if(WIN32)
    set(SFML_ROOT "C:/Program Files (x86)/SFML")
    find_package(SFML REQUIRED main system window graphics audio network)
else()
    find_package(SFML REQUIRED system window graphics audio network)
endif()

if(SFML_FOUND)
    include_directories($(SFML_INCLUDE_DIR))
    target_link_libraries(Fe ${SFML_LIBRARIES})
endif()