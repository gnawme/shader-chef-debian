#ifndef SHADER_CHEF_DUMB_SHADER_OBJECT_HPP
#define SHADER_CHEF_DUMB_SHADER_OBJECT_HPP
/*---------------------------------------------------------------------------*\
| \file     DumbShaderObject.hpp
| \brief    Naive class to manage a GLSL shader
\*---------------------------------------------------------------------------*/
#include <GL/gl.h>

#include <iostream>
#include <memory>

#include "shader_utils.hpp"

//! \class  DumbShaderObject
//! \brief  Naive GLSL shader handling class
class DumbShaderObject
{
public:
    //! \fn     DumbShaderObject
    DumbShaderObject(
        GLuint          shader_type,
        const char*     shader_filename)
        : m_shader_type(shader_type)
        , m_shader_filename(shader_filename)
        , m_shader_handle(glCreateShader(shader_type))
    {
        load_shader_source();
    }

    ~DumbShaderObject()
    {
        glDeleteShader(m_shader_handle);
    }

    //! \fn     compile
    void        compile()
    {
        glCompileShader(m_shader_handle);
        check_compile_status(m_shader_handle);
    }

    //! \fn     delete_shader
    void        delete_shader()
    {
        glDeleteShader(m_shader_handle);
    }

    //! \fn     shader_handle
    GLuint      shader_handle() const
    {
        return m_shader_handle;
    }

private:
    //! \fn     check_compile_status
    void        check_compile_status(
        unsigned int shader_handle)
    {
        GLint result;
        glGetShaderiv(m_shader_handle, GL_COMPILE_STATUS, &result);

        if(result == GL_FALSE) {
            GLint loglen;
            glGetShaderiv(m_shader_handle, GL_INFO_LOG_LENGTH, &loglen);
            if(loglen > 0) {
                std::unique_ptr<char> log(new char[loglen]);

                GLsizei written;
                glGetShaderInfoLog(m_shader_handle, loglen, &written, log.get());
                std::cerr
                << "Shader error log:\n"
                << log.get()
                << std::endl;
            }
        }
    }

    //! \fn     load_shader_source
    void        load_shader_source()
    {
        std::string shader_code(
            load_shader_from_file(m_shader_filename.c_str()));
        const GLchar* code_array[] = {shader_code.c_str()};
        glShaderSource(m_shader_handle, 1, code_array, NULL);
    }

    GLuint      m_shader_type;
    std::string m_shader_filename;
    GLuint      m_shader_handle;
};


#endif//SHADER_CHEF_DUMB_SHADER_OBJECT_HPP
