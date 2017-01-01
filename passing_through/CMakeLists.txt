cmake_minimum_required(VERSION 3.6)
project(passing_through)

set(CMAKE_CXX_STANDARD 11)

include_directories(SHADER_UTILS
        /home/norme/Projects/shader-chef-linux/shader_utils)

set(CMAKE_INCLUDE_PATH
        /usr/include/GLFW
        /usr/include/GL)

set(SOURCE_FILES
        passing_through.cpp
        QuintadecimaRaw.hpp)

set(CMAKE_LIBRARY_PATH /usr/lib/x86_64-linux-gnu)

add_executable(passing_through ${SOURCE_FILES})
target_link_libraries(passing_through -lGL -lGLEW -lglfw)
