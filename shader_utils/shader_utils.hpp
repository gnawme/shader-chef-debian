#ifndef SHADER_CHEF_SHADER_UTILS_HPP
#define SHADER_CHEF_SHADER_UTILS_HPP
/*! GLSL shader utilities ---------------------------------------------------*\
|
\*---------------------------------------------------------------------------*/
#include <fstream>
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

#endif//SHADER_CHEF_SHADER_UTILS_HPP