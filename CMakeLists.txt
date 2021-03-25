cmake_minimum_required (VERSION 3.0)
project (udp2fb)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#version number
set (udp2fb_VERSION_MAJOR 1)
set (udp2fb_VERSION_MINOR 0)

option(BUILD_FOR_PI "BUILD_FOR_PI " OFF)

#indicate the entry point for the executable

set(c_files 
   src/teleop_udp_server.c
   src/teleop_flatbuf_server.c
   src/main.cpp
)

if(BUILD_FOR_PI)
  # set(c_files ${c_files} aaaa.c)
endif()

#add_subdirectory(flacc)

include_directories(../flatcc/include)
include_directories(communications-protocol/src/c_h)

include_directories(inc)


add_executable (udp2fb ${c_files})

# Indicate which libraries to include during the link process.

message(STATUS "dir ${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries (udp2fb ${CMAKE_CURRENT_SOURCE_DIR}/../flatcc/lib/libflatccrt.a)
