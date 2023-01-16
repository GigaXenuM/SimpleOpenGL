#pragma once

namespace Scene
{

class IItem
{
public:
    virtual ~IItem() = default;

    virtual void draw(unsigned int programId) const = 0;
};
} // namespace Scene
