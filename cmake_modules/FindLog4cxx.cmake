

set(FIND_Log4cxx_PATHS
        ${Log4cxx_ROOT}
        $ENV{Log4cxx_ROOT}
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
        /sw
        /opt/local
        /opt/csw
        /opt)

find_path(Log4cxx_INCLUDE_DIR log4cxx.h
        PATH_SUFFIXES include
        PATHS ${FIND_Log4cxx_PATHS})

message(STATUS "${Log4cxx_INCLUDE_DIR}")

set(Log4cxx_FOUND TRUE)
find_library(Log4cxx_LIBRARY
        NAMES log4cxx
        PATH_SUFFIXES lib64 lib
        PATHS ${FIND_Log4cxx_PATHS})

message(STATUS "${Log4cxx_LIBRARY}")

if(NOT Log4cxx_LIBRARY)
    set(Log4cxx_FOUND FALSE)
endif()

if(Log4cxx_FOUND)
    message(STATUS "Found Log4cxx in ${Log4cxx_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "Could NOT find Log4cxx")
endif()