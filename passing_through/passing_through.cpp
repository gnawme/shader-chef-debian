/*---------------------------------------------------------------------------*\
| \\file     passing_through.cpp
| \\author   Norm Evangelista
\*---------------------------------------------------------------------------*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <memory>

#include "DumbProgramObject.hpp"
#include "DumbShaderObject.hpp"
#include "Quintadecima.hpp"
#include "QuintadecimaRaw.hpp"

const std::string SHADER_HOME("/home/norme/Projects/shader-chef-linux/passing_through/");

/*---------------------------------------------------------------------------*\
| \\fn       key_callback
| \\brief    GLFW callback
\*---------------------------------------------------------------------------*/
static void key_callback(
    GLFWwindow* window,
    int         key,
    int         scancode,
    int         action,
    int         mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

/*---------------------------------------------------------------------------*\
|
\*---------------------------------------------------------------------------*/
int main()
{
    /*-----------------------------------------------------------------------*\
    |   Init GLFW, create window and context
    \*-----------------------------------------------------------------------*/
    glfwInit();

    GLFWwindow* passing_through =
        glfwCreateWindow(1920, 1080, "Just Passing Through", NULL, NULL);

    if (!passing_through) {
        throw std::runtime_error("glfwCreateWindow failed");
    }

    glfwMakeContextCurrent(passing_through);
    glfwSetKeyCallback(passing_through, key_callback);

    /*-----------------------------------------------------------------------*\
    |   Init GLEW
    \*-----------------------------------------------------------------------*/
    glewInit();

    /*-----------------------------------------------------------------------*\
    |   Load and compile passthrough vertex and fragment shaders
    \*-----------------------------------------------------------------------*/
    std::string vshader(SHADER_HOME + "vs_basic.glsl");
    DumbShaderObject vs_basic(GL_VERTEX_SHADER, vshader.c_str());

    std::string fshader(SHADER_HOME + "fs_basic.glsl");
    DumbShaderObject fs_basic(GL_FRAGMENT_SHADER, fshader.c_str());

    vs_basic.compile();
    fs_basic.compile();

    /*-----------------------------------------------------------------------*\
    |   Link into shader program
    \*-----------------------------------------------------------------------*/
    DumbProgramObject shaders;
    shaders.attach_shader(vs_basic.shader_handle());
    shaders.attach_shader(fs_basic.shader_handle());

    /*-----------------------------------------------------------------------*\
    |   Map VBO and CBO to shader channels
    \*-----------------------------------------------------------------------*/
    GLuint program_handle = shaders.program_handle();

    /*-----------------------------------------------------------------------*\
    |   Create and populate BOs
    \*-----------------------------------------------------------------------*/
    Quintadecima penta(1.0);
    //QuintadecimaRaw penta;
    float* vertex_data = penta.vertex_buffer();
    float* color_data  = penta.color_buffer_mono();

    GLuint vbo_handles[2];
    glGenBuffers(2, vbo_handles);

    GLuint pbo_handle = vbo_handles[0];
    glBindBuffer(GL_ARRAY_BUFFER, pbo_handle);
    glBufferData(
        GL_ARRAY_BUFFER,
        penta.vertex_data_size() * sizeof(float),
        vertex_data,
        GL_STATIC_DRAW);

    GLuint cbo_handle = vbo_handles[1];
    glBindBuffer(GL_ARRAY_BUFFER, cbo_handle);
    glBufferData(
        GL_ARRAY_BUFFER,
        penta.color_data_size() * sizeof(float),
        color_data,
        GL_STATIC_DRAW);

    /*-----------------------------------------------------------------------*\
    |   Set up and bind VAO
    \*-----------------------------------------------------------------------*/
    GLuint vao_handle;
    glGenVertexArrays(1, &vao_handle);
    glBindVertexArray(vao_handle);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, pbo_handle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, cbo_handle);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    shaders.link_program();

    int width, height;
    glfwGetFramebufferSize(passing_through, &width, &height);
    glViewport(0, 0, width, height);

    float ratio = static_cast<float>(width) / static_cast<float>(height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.0, 1.0, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);

    /*-----------------------------------------------------------------------*\
    |   Drawing loop
    \*-----------------------------------------------------------------------*/
    while(!glfwWindowShouldClose(passing_through)) {
        glUseProgram(program_handle);
        glBindVertexArray(vao_handle);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);

        glfwSwapBuffers(passing_through);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
