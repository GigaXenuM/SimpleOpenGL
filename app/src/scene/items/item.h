#pragma once

namespace Scene
{

class Item
{
public:
    Item(unsigned int element, unsigned int pointCount);
    unsigned int getElement() const;
    unsigned int getPointCount() const;

private:
    unsigned int _element;
    unsigned int _pointCount;
};
}; // namespace Scene
