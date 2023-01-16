#include "mesh.h"

#include <glad/glad.h>

#include <iostream>

std::string getTextureName(TextureType type);

Scene::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
                  std::vector<Texture> textures)
    : _vertices{ vertices }, _indices{ indices }, _textures{ textures }
{
    setup();
}

void Scene::Mesh::setup()
{
    glGenBuffers(1, &_elementBufferId);
    glGenBuffers(1, &_vertexBufferId);
    glGenVertexArrays(1, &_vertexArrayId);

    glBindVertexArray(_vertexArrayId);

    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices.front(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices.front(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, normal)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, texCoords)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, tangent)));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, bitangent)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Scene::Mesh::draw(unsigned int programId) const
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    for (unsigned int textureIndex = 0; textureIndex < _textures.size(); textureIndex++)
    {
        glActiveTexture(GL_TEXTURE0 + textureIndex);

        std::string number;
        TextureType type = _textures[textureIndex].type;
        switch (type)
        {
        case TextureType::Diffuse:
            number = std::to_string(diffuseNr++);
            break;
        case TextureType::Specular:
            number = std::to_string(specularNr++);
            break;
        case TextureType::Normal:
            number = std::to_string(normalNr++);
            break;
        case TextureType::Ambient:
            number = std::to_string(heightNr++);
            break;
        default:
            break;
        }

        glUniform1i(glGetUniformLocation(programId, (getTextureName(type) + number).c_str()),
                    textureIndex);
        glBindTexture(GL_TEXTURE_2D, _textures[textureIndex].id);
    }

    glBindVertexArray(_vertexArrayId);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

std::string getTextureName(TextureType type)
{
    switch (type)
    {
    case TextureType::Diffuse:
        return "texture_diffuse";
    case TextureType::Specular:
        return "texture_specular";
    case TextureType::Normal:
        return "texture_normal";
    case TextureType::Ambient:
        return "texture_ambient";
    default:
        std::cout << "ERROR: Undefiled texture type" << std::endl;
        return "";
    }
}
