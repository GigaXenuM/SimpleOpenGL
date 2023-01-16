#include "scene.h"

#include "model/modelitem/modelitem.h"
#include "shader/program.h"
#include "shader/shader.h"
#include "shader/program.h"

#include "items/graphicsitem.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Scene::Scene::Scene()
{
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

    _items.push_back(new GraphicsItem(_modelItem));
}

void Scene::Scene::draw() const
{
    glUseProgram(_shaderProgram->id());

    // TODO(tkachmaryk): need to realize this in separate class Scene::Camera
    {
        glm::mat4 projection
            = glm::perspective(glm::radians(45.0f), (float)1024 / (float)720, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(-7.0f, 1.0f, 0.0f),
                                     glm::vec3(-7.0f, 1.0f, 0.0f) + glm::vec3(1.0f, 0.0f, 0.0f),
                                     glm::vec3(0.0f, 1.0f, 0.0f));
        _shaderProgram->setMat4("projection", projection);
        _shaderProgram->setMat4("view", view);
    }

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    _shaderProgram->setMat4("model", model);

    for (const auto *item : _items)
        item->draw(_shaderProgram->id());
}

void Scene::Scene::addItem(IItem *item)
{
    _items.push_back(item);
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
