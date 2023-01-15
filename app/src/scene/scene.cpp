#include "scene.h"

#include "modelloader/modelloader.h"
#include "shader/program.h"
#include "shader/shader.h"
#include "shader/program.h"
#include "tools/stb_image.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Scene::Scene::Scene()
{
}

Scene::Scene::~Scene()
{
    delete _model;
}

void Scene::Scene::init()
{
    createShaderProgram("resources/vertex.glsl", "resources/fragment.glsl");

    _model = new ModelLoader("resources/objects/laptop/Lowpoly_Notebook_2.obj");
}

void Scene::Scene::draw() const
{
    glUseProgram(_shaderProgram->id());

    glm::mat4 projection
        = glm::perspective(glm::radians(45.0f), (float)1024 / (float)720, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(-7.0f, 1.0f, 0.0f),
                                 glm::vec3(-7.0f, 1.0f, 0.0f) + glm::vec3(1.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));
    _shaderProgram->setMat4("projection", projection);
    _shaderProgram->setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    _shaderProgram->setMat4("model", model);
    _model->draw(_shaderProgram->id());
}

void Scene::Scene::createShaderProgram(const char *vertexShaderSource,
                                       const char *fragmentShaderSource)
{
    Shader::Shader vertexShader(vertexShaderSource, GL_VERTEX_SHADER);
    Shader::Shader fragmentShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    _shaderProgram = new Shader::Program{ vertexShader.id(), fragmentShader.id() };
}
