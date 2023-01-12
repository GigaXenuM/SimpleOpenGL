#include "program.h"

#include <glad/glad.h>

#include <iostream>

GraphicsShader::Program::Program(unsigned int firstShaderId, unsigned int secondShaderId)
{
    link(firstShaderId, secondShaderId);
}

unsigned int GraphicsShader::Program::id()
{
    return _id;
}

unsigned int GraphicsShader::Program::link(unsigned int firstShaderId, unsigned int secondShaderId)
{
    _id = glCreateProgram();
    glAttachShader(_id, firstShaderId);
    glAttachShader(_id, secondShaderId);

    glLinkProgram(_id);

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(_id, 512, NULL, infoLog);
        std::cout << "ERROR: Shader program linking failed\n" << infoLog << std::endl;
    }

    glDeleteShader(firstShaderId);
    glDeleteShader(secondShaderId);

    return _id;
}
