#include "scene.h"

#include "private/gpudatacontroller/gpudatacontroller.h"
#include "shader/shader.h"
#include "shader/program.h"
#include "items/item.h"

#include <glad/glad.h>

Scene::Scene::Scene() : _gpuDataController{ new GPUDataController }
{
}

Scene::Scene::~Scene()
{
    delete _gpuDataController;
}

void Scene::Scene::init()
{
    createShaderProgram("resources/vertex.glsl", "resources/fragment.glsl");
    _gpuDataController->generateBuffers();

    std::vector<float> vertices{
        0.5f,  0.5f,  0.0f, // top right
        0.5f,  -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f  // top left
    };
    std::vector<unsigned int> indices{ 0, 1, 3, 1, 2, 3 };

    _gpuDataController->setData(0, 3, vertices, indices);
}

void Scene::Scene::draw()
{
    glUseProgram(_shaderProgramId);

    // TODO (tkachmaryk): Change this to the loop where will draw all items on the scene
    Item rectangle(GL_TRIANGLES, 6);

    _items.push_back(&rectangle);

    for (const auto &item : _items)
        _gpuDataController->draw(*item);
}

std::vector<Scene::Item *> Scene::Scene::items()
{
    return _items;
}

void Scene::Scene::createShaderProgram(const char *vertexShaderSource,
                                       const char *fragmentShaderSource)
{
    Shader::Shader vertexShader(vertexShaderSource, GL_VERTEX_SHADER);
    Shader::Shader fragmentShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    Shader::Program shaderProgram(vertexShader.id(), fragmentShader.id());
    _shaderProgramId = shaderProgram.id();
}
