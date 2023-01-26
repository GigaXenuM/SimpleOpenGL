#pragma once

#include "private/sceneimpl.h"

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
class Camera;

class Scene : public Private::Scene::SceneImpl
{
public:
    explicit Scene(int width, int height);
    ~Scene();

    void init();
    void draw() const;
    void addItem(IItem *item);

    void handleEvent(Event *event) override;

private:
    void createShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource);

    const std::vector<IItem *> &items();

    Camera *_camera{ nullptr };
    std::shared_ptr<Model::ModelItem> _modelItem{ nullptr };
    Shader::Program *_shaderProgram{ nullptr };
    std::vector<IItem *> _items;
};
} // namespace Scene
