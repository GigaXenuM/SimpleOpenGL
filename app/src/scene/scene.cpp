#include "scene.h"

#include <glad/glad.h>

#include "camera/camera.h"
#include "model/modelitem/modelitem.h"
#include "shader/program.h"
#include "shader/shader.h"
#include "shader/program.h"

#include "items/graphicsitem.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

Scene::Scene::Scene(int width, int height)
    : _camera{ new Camera(45.0, static_cast<double>(width) / static_cast<double>(height), 100.0) }
{
    addEventHandler(_camera);
}

Scene::Scene::~Scene()
{
    delete _shaderProgram;
    for (auto *item : _items)
        delete item;
}

void Scene::Scene::init()
{
    createShaderProgram("resources/vertex.glsl", "resources/fragment.glsl");
    _modelItem
        = std::make_shared<Model::ModelItem>("resources/objects/laptop/Lowpoly_Notebook_2.obj");
    _modelItem->loadModel();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, 1.5f, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

    auto graphicsItem{ new GraphicsItem(_modelItem) };
    graphicsItem->setModel(model);

    _items.push_back(graphicsItem);

    _camera->setPosition({ 0.0, 0.0, 7.0 });
}

void Scene::Scene::draw() const
{
    _camera->update();

    glUseProgram(_shaderProgram->id());

    _shaderProgram->setMat4("projection", _camera->projection());
    _shaderProgram->setMat4("view", _camera->view());

    for (const auto *item : _items)
    {
        _shaderProgram->setMat4("model", item->model());
        auto &model = const_cast<glm::mat4 &>(item->model());
        model = glm::rotate(model, static_cast<float>(std::sin(glfwGetTime()) * 0.0005),
                            glm::vec3(0.0f, 1.0f, 0.0f));

        item->draw(_shaderProgram->id());
    }
}

void Scene::Scene::addItem(IItem *item)
{
    _items.push_back(item);
}

void Scene::Scene::handleEvent(Event *event)
{
    using Private::Scene::SceneImpl;

    SceneImpl::handleEvent(event);
}

const std::vector<Scene::IItem *> &Scene::Scene::items()
{
    return _items;
}

void Scene::Scene::createShaderProgram(const char *vertexShaderSource,
                                       const char *fragmentShaderSource)
{
    Shader::Shader vertexShader(vertexShaderSource, GL_VERTEX_SHADER);
    Shader::Shader fragmentShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    _shaderProgram = new Shader::Program{ vertexShader.id(), fragmentShader.id() };
}
