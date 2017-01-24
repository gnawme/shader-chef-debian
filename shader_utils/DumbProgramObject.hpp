#ifndef SHADER_CHEF_DUMB_PROGRAM_OBJECT_HPP
#define SHADER_CHEF_DUMB_PROGRAM_OBJECT_HPP
/*! Naive class to manage a GLSL shader -------------------------------------*\
|
\*---------------------------------------------------------------------------*/
#include <GL/gl.h>

#include <iostream>
#include <memory>

//! \class  DumbProgramObject
//! \brief  Naive GLSL shader program class
class DumbProgramObject
{
public:
    //! \fn     DumbProgramObject
    DumbProgramObject()
        : m_program_handle(glCreateProgram())
    {}

    //! \fn     attach_shader
    void        attach_shader(GLuint shader_handle)
    {
        glAttachShader(m_program_handle, shader_handle);
    }

    //! \fn     link_program
    void        link_program()
    {
        glLinkProgram(m_program_handle);
        verify_program();
    }

    //! \fn     program_handle
    GLuint      program_handle() const
    {
        return m_program_handle;
    }

    //! \fn     verify_program
    void        verify_program()
    {
        GLint status;
        glGetProgramiv(m_program_handle, GL_LINK_STATUS, &status);
        if (status == GL_FALSE) {
            std::cerr << "Failed to link shader program!" << std::endl;

            GLint log_length;
            glGetProgramiv(m_program_handle, GL_INFO_LOG_LENGTH, &log_length);
            if (log_length > 0) {
                std::unique_ptr<char> log{new char[log_length]};
                GLsizei written;
                glGetProgramInfoLog(m_program_handle, log_length, &written, log.get());
                std::cerr
                    << "Program log: " << std::endl
                    << log.get();
            }
        }
    }

private:
    GLuint      m_program_handle;

};

#endif//SHADER_CHEF_DUMB_PROGRAM_OBJECT_HPP