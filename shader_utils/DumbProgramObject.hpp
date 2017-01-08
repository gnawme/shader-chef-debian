#ifndef SHADER_CHEF_DUMB_PROGRAM_OBJECT_HPP
#define SHADER_CHEF_DUMB_PROGRAM_OBJECT_HPP
/*! Naive class to manage a GLSL shader -------------------------------------*\
|
\*---------------------------------------------------------------------------*/
#include <GL/gl.h>

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
    }

    //! \fn     program_handle
    GLuint      program_handle() const
    {
        return m_program_handle;
    }

private:
    GLuint      m_program_handle;

};

#endif//SHADER_CHEF_DUMB_PROGRAM_OBJECT_HPP