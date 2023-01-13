#pragma once

namespace Scene
{
class GPUDataController;

class Scene
{
public:
    Scene();
    ~Scene();

    void init();

    void draw();

private:
    void createShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource);

    GPUDataController *_gpuDataController{ nullptr };

    unsigned int _shaderProgramId{ 0 };
};
} // namespace Scene
