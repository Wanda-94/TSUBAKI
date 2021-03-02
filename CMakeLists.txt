cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

if(WIN32)
    message("build platform WIN32")
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        message("build type Debug")
    endif()
    if(CMAKE_BUILD_TYPE MATCHES Release)
        message("build type Release")
    endif()
endif()

project(TSUBAKI)

add_executable(TSUBAKI ./src/main.cpp ./3rdpart/GLAD/src/glad.c)   

add_subdirectory("./3rdpart")

