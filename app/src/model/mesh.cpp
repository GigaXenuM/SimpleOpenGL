#include "mesh.h"

#include <glad/glad.h>

namespace Model
{
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
    : _vertices{ std::move(vertices) }, _indices{ indices }
{
}

const std::vector<Vertex> &Mesh::vertices() const
{
    return _vertices;
}

unsigned int Mesh::verticesMemorySize() const
{
    return _vertices.size() * sizeof(Vertex);
}

unsigned int Mesh::verticesCount() const
{
    return _vertices.size();
}

const std::vector<unsigned int> &Mesh::indices() const
{
    return _indices;
}

unsigned int Mesh::indicesMemorySize() const
{
    return _indices.size() * sizeof(unsigned int);
}

unsigned int Mesh::indicesCount() const
{
    return _indices.size();
}
} // namespace Model
