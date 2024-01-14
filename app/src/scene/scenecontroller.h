#pragma once

#include "event/eventhandler.h"
#include "model/modelcontroller.h"

#include <glm/glm.hpp>

#include <memory>
#include <vector>

namespace Model
{
class Item;
}

namespace GPU
{
class IProgram;
enum class ShaderType;
} // namespace GPU

namespace Scene
{

class IItem;
class Camera;

class Controller : public EventHandler
{
    using ShaderProgramMap = std::unordered_map<GPU::ShaderType, std::shared_ptr<GPU::IProgram>>;

public:
    explicit Controller(std::shared_ptr<Model::Controller> modelController,
                        ShaderProgramMap shaderProgramMap, int width, int height);
    void render() const;

    void createGraphicsItem(Utils::InternalId modelId, glm::mat4 model,
                            GPU::ShaderType shaderType);

private:
    std::shared_ptr<Model::Controller> _modelController;

    std::shared_ptr<Camera> _camera;

    std::vector<std::shared_ptr<IItem>> _items;
    std::unordered_map<GPU::ShaderType, std::shared_ptr<GPU::IProgram>> _shaderPrograms;
};
} // namespace Scene
