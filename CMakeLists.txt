cmake_minimum_required(VERSION 3.4)
project(autopledge_insert)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/cmd-c/src/app.cpp
    src/cmd-insert/src/app.cpp
    src/cmd-ld/src/app.cpp
    src/libannotatesyscalls/include/pass.hpp
    src/libannotatesyscalls/include/syscall.hpp
    src/libannotatesyscalls/src/pass.cpp
    src/libannotatesyscalls/src/syscall.cpp
    src/libs/json/include/json.hpp
    src/CMakeLists.txt
    README.md)

add_executable(autopledge_insert ${SOURCE_FILES})