cmake_minimum_required(VERSION 3.4 FATAL_ERROR) #heheheh
project(autopledge-insert CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS -std=c++1z")

add_subdirectory(libs)
add_subdirectory(cmd-insert)
add_subdirectory(cmd-c)
add_subdirectory(cmd-ld)
add_subdirectory(libmodifysource)