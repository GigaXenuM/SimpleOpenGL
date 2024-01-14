#include "contentcontroller.h"

#include "GPU-tools/shader.h"
#include "GPU-tools/program.h"
#include "GPU-tools/shadertype.h"

#include "shadercontext.h"
#include "mesh-loader/meshloader.h"

#include "scene/scenecontroller.h"

#include <glm/ext/matrix_transform.hpp>
#include <glad/glad.h>

namespace Content
{
Controller::Controller(int width, int height)
    : _modelController{ std::make_shared<Model::Controller>() },
      _sceneController{ std::make_shared<Scene::Controller>(_modelController, shaderProgramMap(),
                                                            width, height) }
{
    createContent();
}

void Controller::render() const
{
    _sceneController->render();
}

std::shared_ptr<Model::Controller> Controller::modelController() const
{
    return _modelController;
}

std::shared_ptr<Scene::Controller> Controller::sceneController() const
{
    return _sceneController;
}

std::shared_ptr<GPU::IProgram> Controller::createShaderProgram(const char *vertexShaderSource,
                                                               const char *fragmentShaderSource)
{
    const GPU::Shader vertexShader(vertexShaderSource, GL_VERTEX_SHADER);
    const GPU::Shader fragmentShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    return std::make_shared<GPU::Program>(vertexShader.id(), fragmentShader.id());
}

Controller::ShaderProgramMap Controller::shaderProgramMap()
{
    ShaderProgramMap map;

    for (GPU::ShaderType type = GPU::ShaderType::Common; type <= GPU::ShaderType::MAX_VALUE;
         type = GPU::ShaderType(static_cast<int>(type) + 1))
    {
        const ShaderContext context{ shaderContextBy(type) };
        map.emplace(type, createShaderProgram(context.vertexShaderPath.c_str(),
                                              context.fragmentShaderPath.c_str()));
    }

    return map;
}

std::vector<std::string> Controller::modelPathes()
{
    return { "resources/models/simple_scene/simple_scene.obj" };
    // return { "resources/models/cube/cube.obj", "resources/models/wolf/wolf.obj",
    //          "resources/models/plant/plant.obj", "resources/models/backpack/backpack.obj" };
}

void Controller::createContent()
{
    loadModels();

    const float step{ 5.f };
    float xModelPos{ 0.f };

    for (const auto modelId : _modelController->itemIds())
    {
        glm::mat4 model3D = glm::mat4(1.0f);
        model3D = glm::translate(model3D, glm::vec3(xModelPos, 0.f, -5.f));
        model3D = glm::scale(model3D, glm::vec3(2.f));
        xModelPos += step;

        _sceneController->createGraphicsItem(modelId, model3D, GPU::ShaderType::Common);
    }
}

void Controller::loadModels()
{
    using MeshPtr = std::shared_ptr<Model::Mesh>;

    for (const std::string &modelPath : modelPathes())
    {
        std::vector<MeshPtr> meshes{ MeshLoader::load(modelPath.c_str()) };
        _modelController->createModelItem(std::move(meshes));
    }
}

} // namespace Content
