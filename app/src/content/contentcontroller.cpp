#include "contentcontroller.h"

#include "GPU-tools/shader.h"
#include "GPU-tools/program.h"
#include "glm/ext/matrix_transform.hpp"
#include "scene/scenecontroller.h"
#include "shadercontext.h"
#include "model/obj-loader/objloader.h"

#include <glad/glad.h>

namespace Content
{
Controller::Controller(int width, int height)
    : _modelController{ std::make_shared<Model::Controller>() },
      _sceneController{ std::make_shared<Scene::Controller>(_modelController, shaderProgramMap(),
                                                            width, height) }
{
    glm::mat4 model3D = glm::mat4(1.0f);
    model3D = glm::translate(model3D, glm::vec3(0.f, 0.f, -5.f));
    model3D = glm::scale(model3D, glm::vec3(0.01f, 0.01f, 0.01f));

    const auto mesh{ Model::OBJLoader::load("resources/models/cube/cube.obj") };
    _sceneController->createGraphicsItem(mesh, model3D, GPU::ShaderType::Common);

    _sceneController->init();
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

    const GPU::ShaderType type{ GPU::ShaderType::Common };
    const ShaderContext context{ shaderContextBy(type) };
    map.emplace(type, createShaderProgram(context.vertexShaderPath.c_str(),
                                          context.fragmentShaderPath.c_str()));

    return map;
}

} // namespace Content
