#include "shader.h"

#include "utils/file-loader/fileloader.h"

#include <glad/glad.h>

#include <iostream>

namespace GPU
{
Shader::Shader(const char *pathToSource, unsigned int shaderType)
{
    compile(pathToSource, shaderType);
}

unsigned int Shader::compile(const char *pathToSource, unsigned int shaderType)
{
    _shaderId = glCreateShader(shaderType);

    const std::string shaderSource{ Utils::FileLoader::load(pathToSource) };
    const char *shaderSourceCStr{ shaderSource.c_str() };

    glShaderSource(_shaderId, 1, &shaderSourceCStr, nullptr);
    glCompileShader(_shaderId);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(_shaderId, 512, nullptr, infoLog);
        if (shaderType == GL_VERTEX_SHADER)
            std::cout << "ERROR: Vertex shader compilation failed" << std::endl;
        if (shaderType == GL_FRAGMENT_SHADER)
            std::cout << "ERROR: Fragment shader compilation failed" << std::endl;
        std::cout << infoLog << std::endl;
    }

    return _shaderId;
}

unsigned int Shader::id() const
{
    return _shaderId;
}
} // namespace GPU
