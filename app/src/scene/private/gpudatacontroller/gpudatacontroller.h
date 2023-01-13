#pragma once

#include <vector>

namespace Scene
{

class GPUDataController
{
public:
    GPUDataController();

    void generateBuffers();

    void draw(unsigned int element, unsigned int pointCount);

    void setData(size_t layout, size_t packSize, const std::vector<float> &data,
                 const std::vector<unsigned int> &indices);

private:
    unsigned int _elementBufferId{ 0 };
    unsigned int _vertexArrayId{ 0 };
    unsigned int _vertexBufferId{ 0 };
};
} // namespace Scene
