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

namespace
{
    int swap_tracker = 1;
    const std::string SHADER_HOME("/home/norme/Projects/shader-chef-linux/passing_through/");
}

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
    switch (key) {
        case GLFW_KEY_ESCAPE:
        {
            if (action == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, GL_TRUE);
            }
        }

        case GLFW_KEY_UP:
        {
            if (action == GLFW_PRESS) {
                ++swap_tracker;
            }
        }

        default:
            break;
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
    |   Create and populate BOs for generated pentagon
    \*-----------------------------------------------------------------------*/
    Quintadecima penta_gen(1.0);
    float* vertex_data = penta_gen.vertex_buffer();
    float* color_data = penta_gen.color_buffer_mono();

    GLuint gen_vbo_handles[2];
    glGenBuffers(2, gen_vbo_handles);

    GLuint gen_pbo_handle = gen_vbo_handles[0];
    glBindBuffer(GL_ARRAY_BUFFER, gen_pbo_handle);
    glBufferData(
        GL_ARRAY_BUFFER,
        penta_gen.vertex_data_size() * sizeof(float),
        vertex_data,
        GL_STATIC_DRAW);

    GLuint gen_cbo_handle = gen_vbo_handles[1];
    glBindBuffer(GL_ARRAY_BUFFER, gen_cbo_handle);
    glBufferData(
        GL_ARRAY_BUFFER,
        penta_gen.color_data_size() * sizeof(float),
        color_data,
        GL_STATIC_DRAW);

    /*-----------------------------------------------------------------------*\
    |   Set up and bind VAO for generated pentagon
    \*-----------------------------------------------------------------------*/
    GLuint gen_vao_handle;
    glGenVertexArrays(1, &gen_vao_handle);
    glBindVertexArray(gen_vao_handle);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, gen_pbo_handle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, gen_cbo_handle);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    /*-----------------------------------------------------------------------*\
    |   Create and populate BOs for constructed pentagon
    \*-----------------------------------------------------------------------*/
    QuintadecimaRaw penta_raw;
    float* raw_vertex_data = penta_raw.vertex_buffer();
    float* raw_color_data = penta_raw.color_buffer_mono();

    GLuint raw_vbo_handles[2];
    glGenBuffers(2, raw_vbo_handles);

    GLuint raw_pbo_handle = raw_vbo_handles[0];
    glBindBuffer(GL_ARRAY_BUFFER, raw_pbo_handle);
    glBufferData(
        GL_ARRAY_BUFFER,
        penta_raw.vertex_data_size() * sizeof(float),
        raw_vertex_data,
        GL_STATIC_DRAW);

    GLuint raw_cbo_handle = raw_vbo_handles[1];
    glBindBuffer(GL_ARRAY_BUFFER, raw_cbo_handle);
    glBufferData(
        GL_ARRAY_BUFFER,
        penta_raw.color_data_size() * sizeof(float),
        raw_color_data,
        GL_STATIC_DRAW);

    /*-----------------------------------------------------------------------*\
    |   Set up and bind VAO for constructed pentagon
    \*-----------------------------------------------------------------------*/
    GLuint raw_vao_handle;
    glGenVertexArrays(1, &raw_vao_handle);
    glBindVertexArray(raw_vao_handle);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, raw_pbo_handle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, raw_cbo_handle);
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
    while (!glfwWindowShouldClose(passing_through)) {
        glUseProgram(program_handle);

        if (swap_tracker % 2 == 0) {
            glBindVertexArray(gen_vao_handle);
        } else {
            glBindVertexArray(raw_vao_handle);
        }

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);

        glfwSwapBuffers(passing_through);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
