cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

if(WIN32)
    message("build platform WIN32")
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        message("build type Debug")
        add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
    endif()
    if(CMAKE_BUILD_TYPE MATCHES Release)
        message("build type Release")
    endif()
endif()

project(TSUBAKI)

add_executable(TSUBAKI 
./src/main.cpp 
./3rdpart/GLAD/src/glad.c

./src/utility/config.cpp
./src/utility/basic.cpp
./src/utility/initializer.cpp
./src/utility/renderer.cpp
./src/utility/controller.cpp
./src/utility/importer.cpp
./src/utility/TBK/TBKbase.cpp

./src/window/window.cpp

./src/component/material.cpp
./src/component/mesh.cpp
./src/component/shader.cpp
./src/component/object.cpp
./src/component/transform.cpp
./src/component/camera.cpp
./src/component/light.cpp
./src/component/texture.cpp

./src/hardware/interface.cpp

./src/gamebase/actor.cpp
)   

target_include_directories(TSUBAKI PRIVATE ./include/)

add_subdirectory("./3rdpart")


