#include "gpudatacontroller.h"

#include <glad/glad.h>

Scene::GPUDataController::GPUDataController()
{
}

void Scene::GPUDataController::generateBuffers()
{
    glGenBuffers(1, &_elementBufferId);
    glGenBuffers(1, &_vertexBufferId);
    glGenVertexArrays(1, &_vertexArrayId);
}

void Scene::GPUDataController::draw(unsigned int element, unsigned int pointCount)
{
    glBindVertexArray(_vertexArrayId);

    glDrawElements(element, pointCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Scene::GPUDataController::setData(size_t layout, size_t packSize,
                                       const std::vector<float> &data,
                                       const std::vector<unsigned int> &indices)
{
    glBindVertexArray(_vertexArrayId);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferId);

    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data.front()), &data.front(),
                 GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices.front()),
                 &indices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(layout, packSize, GL_FLOAT, GL_FALSE, packSize * sizeof(float),
                          static_cast<void *>(0));
    glEnableVertexAttribArray(layout);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
