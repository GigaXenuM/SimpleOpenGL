#pragma once

#include <glm/glm.hpp>

namespace Model
{

struct Vertex
{
    glm::vec3 position{ glm::vec3(0.0f, 0.0f, 0.0f) };
    glm::vec2 texturePosition{ glm::vec2(0.0f, 0.0f) };
    glm::vec3 normal{ glm::vec3(0.0f, 0.0f, 0.0f) };
};
} // namespace Model
