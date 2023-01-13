#pragma once

#include <vector>

namespace Scene
{

class TestItem
{
public:
    TestItem();

private:
    unsigned int _pointCount;
    unsigned int _type;
    std::vector<int> _indices;
    std::vector<float> _vertices;
};
} // namespace Scene
