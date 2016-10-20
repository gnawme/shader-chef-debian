cmake_minimum_required(VERSION 3.6)
project(shader_chef_debian)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lGL -lGLEW -lglfw")

set(CMAKE_INCLUDE_PATH
    /usr/include/GLFW
    /usr/include/GL)

set(SOURCE_FILES
    shadertest.cpp)

set(CMAKE_LIBRARY_PATH /usr/lib/x86_64-linux-gnu)

add_executable(shader_chef_debian ${SOURCE_FILES})