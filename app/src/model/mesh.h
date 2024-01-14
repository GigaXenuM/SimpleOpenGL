#pragma once

#include "vertex.h"

#include <vector>

namespace Model
{
class Mesh
{
public:
    explicit Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    const std::vector<Vertex> &vertices() const;
    unsigned int verticesMemorySize() const;
    unsigned int verticesCount() const;

    const std::vector<unsigned int> &indices() const;
    unsigned int indicesMemorySize() const;
    unsigned int indicesCount() const;

private:
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
};
} // namespace Model
