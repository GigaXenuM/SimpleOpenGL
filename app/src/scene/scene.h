#pragma once

#include <vector>

namespace Scene
{
class GPUDataController;
class Item;

class Scene
{
public:
    Scene();
    ~Scene();

    void init();
    void draw();

    std::vector<Item *> items();

private:
    void createShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource);

    GPUDataController *_gpuDataController{ nullptr };

    unsigned int _shaderProgramId{ 0 };

    std::vector<Item *> _items;
};
} // namespace Scene
