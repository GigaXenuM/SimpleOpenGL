#pragma once

#include "tools/texture.h"
#include "tools/vertex.h"

#include <string>
#include <vector>

using namespace Tools;

namespace Scene
{

class Mesh
{
public:
    explicit Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
                  std::vector<Texture> textures);

    void setup();

    void draw(unsigned int programId) const;

private:
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
    std::vector<Texture> _textures;

    unsigned int _elementBufferId{ 0 };
    unsigned int _vertexArrayId{ 0 };
    unsigned int _vertexBufferId{ 0 };
};
} // namespace Scene
