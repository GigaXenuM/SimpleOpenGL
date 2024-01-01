#include "mesh.h"

#include <glad/glad.h>

namespace Model
{
Mesh::Mesh(std::vector<Vertex> vertices) : _vertices{ std::move(vertices) }
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
} // namespace Model
