#pragma once

#include "vertex.h"

#include <vector>

namespace Model
{
class Mesh
{
public:
    explicit Mesh(std::vector<Vertex> vertices);

    const std::vector<Vertex> &vertices() const;
    unsigned int verticesMemorySize() const;
    unsigned int verticesCount() const;

private:
    std::vector<Vertex> _vertices;
};
} // namespace Model
