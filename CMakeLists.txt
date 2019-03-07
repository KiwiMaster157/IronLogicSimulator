cmake_minimum_required(VERSION 3.12)
project(Fe)

set(CMAKE_FIND_DEBUG_MODE ON)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(Fe src/Main.cpp src/Console.cpp )# src/Signal.cpp src/Simulator.cpp)


#set(SFML_STATIC_LIBRARIES 1) # Static Linux SFML
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

if(WIN32)
    # Reuben, set this line to the directory containing SFML
    set(SFML_ROOT "C:/Program Files (x86)")
    # Reuben, set this line to the log4cxx root directory
    find_package(SFML REQUIRED main system window graphics audio network)
    find_package(Log4cxx REQUIRED)
else()
    find_package(SFML REQUIRED system window graphics audio network)
    find_package(Log4cxx REQUIRED)
endif()

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Fe ${SFML_LIBRARIES})
endif()
#[[
if(Log4cxx_FOUND)
    include_directories(${Log4cxx_INCLUDE_DIR})
    target_link_libraries(Fe ${Log4cxx_LIBRARY})
endif()
]]
include_directories(/usr/include)
target_link_libraries(Fe /usr/lib64/libglog.so)