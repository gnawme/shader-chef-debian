/*! Draws a pentagon --------------------------------------------------------*\
| Exercise using a programmatically generated texture
\*---------------------------------------------------------------------------*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL.h>

#include <array>
#include <cstring>
#include <stdexcept>

#include "DumbProgramObject.hpp"
#include "DumbShaderObject.hpp"
#include "QuintadecimaTex.hpp"

namespace
{
    const std::string SHADER_HOME("/home/norme/Projects/shader-chef-linux/textiled/");
}

/*! -------------------------------------------------------------------------*\
| \fn       key_callback
| \brief    GLFW callback
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

        default:
            break;
    }
}

/*! -------------------------------------------------------------------------*\
| \fn       load_uniform_block
\*---------------------------------------------------------------------------*/
void load_uniform_block(GLuint program_handle)
{
    GLuint block_index = glGetUniformBlockIndex(program_handle, "BlobSettings");

    GLint block_size;
    glGetActiveUniformBlockiv(program_handle, block_size, GL_UNIFORM_BLOCK_DATA_SIZE, &block_size);
    GLubyte* block_buffer(new GLubyte[block_size]);

    // Query for the offsets of each block variable
    const GLchar* block_names[] = {
        "BlobSettings.InnerColor", "BlobSettings.OuterColor",
        "BlobSettings.RadiusInner", "BlobSettings.RadiusOuter" };

    GLuint indices[4];
    glGetUniformIndices(program_handle, 4, block_names, indices);


    GLint offset[4];
    glGetActiveUniformsiv(program_handle, 4, indices, GL_UNIFORM_OFFSET, offset);

    GLfloat inner_color[] = {1.0f, 1.0f, 0.75f, 1.0f};
    GLfloat outer_color[] = {0.0f, 0.0f, 0.0f, 0.0f};
    GLfloat inner_radius = 0.25f;
    GLfloat outer_radius = 0.45f;

    std::copy(inner_color, inner_color+4, block_buffer + offset[0]);
    std::copy(outer_color, outer_color+4, block_buffer + offset[1]);
    std::copy(&inner_radius, &inner_radius+1, block_buffer + offset[2]);
    std::copy(&outer_radius, &outer_radius+4, block_buffer + offset[3]);

    GLuint ubo_handle;
    glGenBuffers(1, &ubo_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_handle);
    glBufferData(GL_UNIFORM_BUFFER, block_size, block_buffer, GL_DYNAMIC_DRAW);

    glBindBufferBase(GL_UNIFORM_BUFFER, block_index, ubo_handle);
}

/*! -------------------------------------------------------------------------*\
| \fn       load_shaders
\*---------------------------------------------------------------------------*/
GLuint load_shaders()
{
    /*-----------------------------------------------------------------------*\
    |   Load and compile texture mapping vertex and fragment shaders
    \*-----------------------------------------------------------------------*/
    std::string vshader(SHADER_HOME + "vs_blob.glsl");
    DumbShaderObject vs_blob(GL_VERTEX_SHADER, vshader.c_str());

    std::string fshader(SHADER_HOME + "fs_blob.glsl");
    DumbShaderObject fs_blob(GL_FRAGMENT_SHADER, fshader.c_str());

    vs_blob.compile();
    fs_blob.compile();

    /*-----------------------------------------------------------------------*\
    |   Link into shader program
    \*-----------------------------------------------------------------------*/
    DumbProgramObject shaders;
    shaders.attach_shader(vs_blob.shader_handle());
    shaders.attach_shader(fs_blob.shader_handle());
    shaders.link_program();

    return shaders.program_handle();
}

/*! -------------------------------------------------------------------------*\
| \fn       main
\*---------------------------------------------------------------------------*/
int main(int argc, char** argv)
{
    /*-----------------------------------------------------------------------*\
    |   Init GLFW, create window and context, init GLEW
    \*-----------------------------------------------------------------------*/
    glfwInit();

    GLFWwindow* blobby_tile =
        glfwCreateWindow(1280, 720, "Textured Pentatile?", NULL, NULL);

    if (!blobby_tile) {
        throw std::runtime_error("glfwCreateWindow failed");
    }

    glfwMakeContextCurrent(blobby_tile);
    glfwSetKeyCallback(blobby_tile, key_callback);

    glewInit();

    /*-----------------------------------------------------------------------*\
    |   Load shaders
    \*-----------------------------------------------------------------------*/
    GLuint program_handle = load_shaders();

    /*-----------------------------------------------------------------------*\
    |   Create and populate BOs for constructed pentagon
    \*-----------------------------------------------------------------------*/
    QuintadecimaTex pentatex;

    GLuint pent_vbo_handles[3];
    glGenBuffers(3, pent_vbo_handles);

    GLuint pent_pbo_handle = pent_vbo_handles[0];
    glBindBuffer(GL_ARRAY_BUFFER, pent_pbo_handle);
    float* pent_vertex_data = pentatex.vertex_buffer();
    glBufferData(
        GL_ARRAY_BUFFER,
        pentatex.vertex_data_size() * sizeof(float),
        pent_vertex_data,
        GL_STATIC_DRAW);

    GLuint pent_cbo_handle = pent_vbo_handles[1];
    glBindBuffer(GL_ARRAY_BUFFER, pent_cbo_handle);
    float* pent_color_data = pentatex.color_buffer_mono();
    glBufferData(
        GL_ARRAY_BUFFER,
        pentatex.color_data_size() * sizeof(float),
        pent_color_data,
        GL_STATIC_DRAW);

    GLuint pent_tco_handle = pent_vbo_handles[2];
    float* pent_texcoord_data = pentatex.texture_buffer();
    glBindBuffer(GL_ARRAY_BUFFER, pent_tco_handle);
    glBufferData(
        GL_ARRAY_BUFFER,
        pentatex.texture_coord_size() * sizeof(float),
        pent_texcoord_data,
        GL_STATIC_DRAW);

    /*-----------------------------------------------------------------------*\
    |   Set up and bind VAO for constructed pentagon
    \*-----------------------------------------------------------------------*/
    GLuint pent_vao_handle;
    glGenVertexArrays(1, &pent_vao_handle);
    glBindVertexArray(pent_vao_handle);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, pent_pbo_handle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, pent_cbo_handle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, pent_tco_handle);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    /*-----------------------------------------------------------------------*\
    |   Generate texture
    \*-----------------------------------------------------------------------*/
    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    /*-----------------------------------------------------------------------*\
    |   Set up texture params
    \*-----------------------------------------------------------------------*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /*-----------------------------------------------------------------------*\
    |   Load and generate
    \*-----------------------------------------------------------------------*/
    int imgwidth, imgheight;
    std::string imgname = SHADER_HOME + "container.jpg";
    unsigned char* container = SOIL_load_image(imgname.c_str(), &imgwidth, &imgheight, 0, SOIL_LOAD_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgwidth, imgheight, 0, GL_RGB, GL_UNSIGNED_BYTE, container);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(container);
    glBindTexture(GL_TEXTURE_2D, 0);

    /*-----------------------------------------------------------------------*\
    |   Construct transform to center polygons
    \*-----------------------------------------------------------------------*/
    glm::vec3 minima, maxima;
    pentatex.get_extrema(minima, maxima);

    float x_center = 0.5 * (maxima.x - minima.x);
    float y_center = 0.5 * (maxima.y - minima.y);

    glm::mat4 id_matrix = glm::mat4(1.0);
    glm::mat4 trans_matrix = glm::translate(id_matrix, glm::vec3(x_center, y_center, 0.0));

    /*-----------------------------------------------------------------------*\
    |   Set up viewing
    \*-----------------------------------------------------------------------*/
    int width, height;
    glfwGetFramebufferSize(blobby_tile, &width, &height);
    glViewport(0, 0, width, height);

    float ratio = static_cast<float>(width) / static_cast<float>(height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.0, 1.0, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);

    GLuint uniform_loc = glGetUniformLocation(program_handle, "RotationMatrix");

    /*-----------------------------------------------------------------------*\
    |   Print out active attributes and uniforms
    \*-----------------------------------------------------------------------*/
    print_active_attributes(program_handle);
    print_active_uniforms(program_handle);

    /*-----------------------------------------------------------------------*\
    |   Drawing loop
    \*-----------------------------------------------------------------------*/
    while (!glfwWindowShouldClose(blobby_tile)) {
        glfwPollEvents();

        if (uniform_loc >= 0) {
            glUniformMatrix4fv(uniform_loc, 1, GL_TRUE, &trans_matrix[0][0]);
        }

        glUseProgram(program_handle);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(pent_vao_handle);

        glClearColor(0.18f, 0.18f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);

        glfwSwapBuffers(blobby_tile);
    }

    glDeleteVertexArrays(1, &pent_vao_handle);
    glDeleteBuffers(3, pent_vbo_handles);

    glfwTerminate();
    return EXIT_SUCCESS;


}