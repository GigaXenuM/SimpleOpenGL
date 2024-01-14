#include "modelcontroller.h"

#include "model/item/item.h"
#include "GPU-tools/gpucontext.h"
#include "model/mesh.h"

#include <glad/glad.h>

#include <cassert>
#include <iostream>

namespace Model
{
Controller::Controller()
{
}

Utils::InternalId Controller::createModelItem(std::vector<std::shared_ptr<Mesh>> meshes)
{
    const Utils::InternalId id;
    _itemMap.emplace(id, std::make_shared<Model::Item>(std::move(meshes)));
    _itemIds.push_back(id);

    loadOnGPU(id);

    return id;
}

std::vector<Utils::InternalId> Controller::itemIds() const
{
    return _itemIds;
}

std::shared_ptr<IItem> Controller::findItem(Utils::InternalId modelId) const
{
    const auto it{ _itemMap.find(modelId) };

    const bool isItemFound{ it != _itemMap.cend() };
    if (!isItemFound)
        std::cout << "Item with model id " << modelId.get() << "not found." << std::endl;

    return isItemFound ? it->second : nullptr;
}

void Controller::loadOnGPU(Utils::InternalId modelId)
{
    const std::shared_ptr<IItem> item{ findItem(modelId) };
    assert(item != nullptr);

    for (const std::shared_ptr<Mesh> mesh : item->meshes())
    {
        GPU::Context gpuContext;

        glGenBuffers(1, &gpuContext.vertexBufferId);
        glGenVertexArrays(1, &gpuContext.vertexArrayId);
        glGenBuffers(1, &gpuContext.elementBufferId);

        glBindVertexArray(gpuContext.vertexArrayId);

        glBindBuffer(GL_ARRAY_BUFFER, gpuContext.vertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, mesh->verticesMemorySize(), &mesh->vertices().front(),
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gpuContext.elementBufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indicesMemorySize(), &mesh->indices().front(),
                     GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<void *>(0));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<void *>(offsetof(Vertex, texturePosition)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<void *>(offsetof(Vertex, normal)));

        glBindVertexArray(NULL);
        glBindBuffer(GL_ARRAY_BUFFER, NULL);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

        gpuContext.indicesSize = mesh->indicesCount();

        item->addGPUContext(gpuContext);
    }
}

void Controller::render(Utils::InternalId modelId) const
{
    const std::shared_ptr<Model::IItem> modelItem{ findItem(modelId) };

    for (const GPU::Context &gpuContext : modelItem->GPUContext())
    {
        glBindVertexArray(gpuContext.vertexArrayId);
        glDrawElements(GL_TRIANGLES, gpuContext.indicesSize, GL_UNSIGNED_INT, NULL);
        glBindVertexArray(NULL);
    }

    glActiveTexture(GL_TEXTURE0);
}
} // namespace Model
