#include "shader.h"

#include "fileLoader/fileloader.h"

#include <glad/glad.h>

#include <iostream>

Shader::Shader(const char *pathToSource, unsigned int shaderType)
{
    compile(pathToSource, shaderType);
}

unsigned int Shader::compile(const char *pathToSource, unsigned int shaderType)
{
    _shaderId = glCreateShader(shaderType);
    const char *shaderSource{ FileLoader::load(pathToSource) };
    glShaderSource(_shaderId, 1, &shaderSource, nullptr);
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

unsigned int Shader::id()
{
    return _shaderId;
}
