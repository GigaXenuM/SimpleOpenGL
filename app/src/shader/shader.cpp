#include "shader.h"

#include "model/fileLoader/fileloader.h"

#include <glad/glad.h>

#include <iostream>

Shader::Shader::Shader(const char *pathToSource, unsigned int shaderType)
{
    compile(pathToSource, shaderType);
}

unsigned int Shader::Shader::compile(const char *pathToSource, unsigned int shaderType)
{
    _shaderId = glCreateShader(shaderType);

    const std::string shaderSource{ FileLoader::load(pathToSource) };
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

unsigned int Shader::Shader::id() const
{
    return _shaderId;
}
