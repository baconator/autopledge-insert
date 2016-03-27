cmake_minimum_required(VERSION 3.4 FATAL_ERROR) #heheheh
project(autopledge-insert CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_subdirectory(libs)
add_subdirectory(cmd-insert)
add_subdirectory(libannotatesyscalls)
add_subdirectory(libmodifysource)