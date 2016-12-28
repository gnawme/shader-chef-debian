/*
 * shadertest.cpp
 *
 *  Created on: Mar 15, 2016
 *      Author: nevangelista
 */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <vector>

inline const char* get_string(unsigned int oglString)
{
    return reinterpret_cast<const char*>(glGetString(oglString));
}

int main()
{
    // Init GFLW
    glfwInit();

    // Window and context
    GLFWwindow* helloOGL = glfwCreateWindow(1920, 1080, "Hello, OpenGL", NULL, NULL);
    glfwMakeContextCurrent(helloOGL);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cerr
                << "Error initializing GLEW: "
                << glewGetErrorString(err)
                << std::endl;
    }

    // Get OpenGL properties
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    std::string renderer(get_string(GL_RENDERER));
    std::string vendor(get_string(GL_VENDOR));
    std::string version(get_string(GL_VERSION));
    std::string glsl(get_string(GL_SHADING_LANGUAGE_VERSION));

    // Print OpenGL properties
    std::cout
    << "OpenGL version "
    << version
    << "(" << major << "." << minor << ")" << std::endl
    << "Vendor:        " << vendor << std::endl
    << "Renderer:      " << renderer << std::endl
    << "GLSL:          " << glsl << std::endl;

    // Acquire OpenGL extensions
    GLint num_extensions;
    glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);

    std::vector<std::string> extensions;
    for(int i = 0; i < num_extensions; ++i) {
        extensions.push_back(
            reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i)));
    }

    // Print them out
    std::cout
    << extensions.size()
    << " OpenGL extensions: " << std::endl;
    for(auto it : extensions) {
        std::cout
                << "\t"
                << it
                << std::endl;
    }


    //   Buh-bye
    glfwDestroyWindow(helloOGL);
    glfwTerminate();
    return EXIT_SUCCESS;
}
