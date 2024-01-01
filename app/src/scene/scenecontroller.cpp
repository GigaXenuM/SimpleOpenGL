#include "scenecontroller.h"

#include "GPU-tools/iprogram.h"
#include "camera/camera.h"
#include "model/item/item.h"

#include "items/graphicsitem.h"
#include "model/mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Scene
{

Controller::Controller(std::shared_ptr<Model::Controller> modelController,
                       ShaderProgramMap shaderProgramMap, int width, int height)
    : _modelController{ std::move(modelController) },
      _camera{ std::make_shared<Camera>(45.0,
                                        static_cast<double>(width) / static_cast<double>(height),
                                        100.0) },
      _shaderPrograms{ std::move(shaderProgramMap) }
{
    addEventHandler(_camera.get());
}

void Controller::init()
{
    for (auto item : _items)
        _modelController->loadOnGPU(item->modelId());
}

void Controller::render() const
{
    _camera->update();

    for (const auto &item : _items)
    {
        const std::shared_ptr<GPU::IProgram> shaderProgram{ _shaderPrograms.at(
            item->shaderType()) };

        shaderProgram->use();

        shaderProgram->setMat4("projection", _camera->projection());
        shaderProgram->setMat4("view", _camera->view());
        shaderProgram->setMat4("model", item->model3D());

        _modelController->render(item->modelId());
    }
}

void Controller::createGraphicsItem(std::shared_ptr<Model::Mesh> mesh, glm::mat4 model,
                                    GPU::ShaderType shaderType)
{
    const Utils::InternalId modelId{ _modelController->createModelItem(mesh) };
    const auto graphicsIttem{ std::make_shared<GraphicsItem>(modelId, model, shaderType) };
    _items.push_back(graphicsIttem);
}
} // namespace Scene
