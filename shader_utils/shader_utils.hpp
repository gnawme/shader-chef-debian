#ifndef SHADER_CHEF_SHADER_UTILS_HPP
#define SHADER_CHEF_SHADER_UTILS_HPP
/*! GLSL shader utilities ---------------------------------------------------*\
|
\*---------------------------------------------------------------------------*/
#include <GL/gl.h>
#include <fstream>
#include <iomanip>
#include <sstream>

/*!--------------------------------------------------------------------------*\
| \fn       load_shader_from_file
| \brief    Loads a shader into a string from a file
| \see      http://stackoverflow.com/a/2602258/124755
\*---------------------------------------------------------------------------*/
std::string load_shader_from_file
(const char* filename)
{
    std::ifstream infile(filename);
    std::stringstream buffer;
    buffer << infile.rdbuf();
    return std::string(buffer.str());
}

/*!--------------------------------------------------------------------------*\
| \fn       print_active_attributes
| \brief    Prints active shader attributes
\*---------------------------------------------------------------------------*/
void print_active_attributes(GLuint program_handle)
{
    GLint maxLength, nAttribs;
    glGetProgramiv(program_handle, GL_ACTIVE_ATTRIBUTES,
                   &nAttribs);

    glGetProgramiv(program_handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
                   &maxLength);

    std::unique_ptr<GLchar> attr_name(new GLchar[maxLength]);

    std::cout << "\n Index | Name" << std::endl;

    for (auto i = 0; i < nAttribs; ++i) {
        GLint written, size;
        GLenum type;
        glGetActiveAttrib( program_handle, i, maxLength, &written, &size, &type, attr_name.get() );
        GLint loc_idx = glGetAttribLocation(program_handle, attr_name.get());
        std::cout
            << std::setw(6) << loc_idx
            << " | "
            << attr_name.get() << std::endl;
    }
}

/*!--------------------------------------------------------------------------*\
| \fn       print_active_uniforms
| \brief    Prints active shader attributes
\*---------------------------------------------------------------------------*/
void print_active_uniforms(GLuint program_handle)
{
    GLint nUniforms, maxLength;

    glGetProgramiv( program_handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);
    glGetProgramiv( program_handle, GL_ACTIVE_UNIFORMS, &nUniforms);

    std::unique_ptr<GLchar> uniform_name(new GLchar[maxLength]);

    std::cout << "\n Location | Name" << std::endl;
    for( auto i = 0; i < nUniforms; ++i ) {
        GLint size;
        GLsizei written;
        GLenum type;

        glGetActiveUniform( program_handle, i, maxLength, &written,
                            &size, &type, uniform_name.get() );
        GLint loc_idx = glGetUniformLocation(program_handle, uniform_name.get());
        std::cout
            << std::setw(9) << loc_idx
            << " | "
            << uniform_name.get() << std::endl;
    }
}


#endif//SHADER_CHEF_SHADER_UTILS_HPP