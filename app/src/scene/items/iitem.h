#pragma once

#include <glm/glm.hpp>

namespace Scene
{

class IItem
{
public:
    virtual ~IItem() = default;

    virtual void draw(unsigned int programId) const = 0;
    virtual const glm::mat4 &model() const = 0;
};
} // namespace Scene
