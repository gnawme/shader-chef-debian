cmake_minimum_required(VERSION 3.6)
project(textiled)

set(CMAKE_CXX_STANDARD 11)

include_directories(SHADER_UTILS
/home/norme/Projects/shader-chef-linux/shader_utils)

set(CMAKE_INCLUDE_PATH
/usr/include/GLFW
/usr/include/GL
/usr/local/include)

set(SOURCE_FILES textiled.cpp)
add_executable(textiled ${SOURCE_FILES})
set(CMAKE_LIBRARY_PATH /usr/lib/x86_64-linux-gnu /usr/local/lib)

target_link_libraries(textiled -lSOIL -lGL -lGLEW -lglfw)
