#pragma once

class ModelLoader;
namespace Shader
{
class Program;
}

namespace Scene
{

class Scene
{
public:
    Scene();
    ~Scene();

    void init();

    void draw() const;

private:
    void createShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource);

    ModelLoader *_model{ nullptr };
    Shader::Program *_shaderProgram{ nullptr };
};
} // namespace Scene
