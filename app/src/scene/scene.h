#pragma once

#include <memory>
#include <vector>

namespace Model
{
class ModelItem;
}
namespace Shader
{
class Program;
}

namespace Scene
{

class IItem;

class Scene
{
public:
    Scene();
    ~Scene();

    void init();
    void draw() const;
    void addItem(IItem *item);

    const std::vector<IItem *> &items();

private:
    void createShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource);

    std::shared_ptr<Model::ModelItem> _modelItem{ nullptr };

    Shader::Program *_shaderProgram{ nullptr };

    std::vector<IItem *> _items;
};
} // namespace Scene
