#include "program.h"

#include <glad/glad.h>

#include <iostream>

namespace GPU
{
Program::Program(unsigned int firstShaderId, unsigned int secondShaderId)
{
    link(firstShaderId, secondShaderId);
}

unsigned int Program::id() const
{
    return _id;
}

void Program::use() const
{
    glUseProgram(_id);
}

void Program::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

unsigned int Program::link(unsigned int firstShaderId, unsigned int secondShaderId)
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
} // namespace GPU
