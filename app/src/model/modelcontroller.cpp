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

Utils::InternalId Controller::createModelItem(std::shared_ptr<Model::Mesh> mesh)
{
    const Utils::InternalId id;
    _itemMap.emplace(id, std::make_shared<Model::Item>(std::move(mesh)));

    return id;
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

    const std::shared_ptr<Mesh> mesh{ item->mesh() };

    GPU::Context gpuContext;

    glGenBuffers(1, &gpuContext.vertexBufferId);
    glGenVertexArrays(1, &gpuContext.vertexArrayId);

    glBindVertexArray(gpuContext.vertexArrayId);

    glBindBuffer(GL_ARRAY_BUFFER, gpuContext.vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, mesh->verticesMemorySize(), &mesh->vertices().front(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, texturePosition)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    item->setGPUContext(gpuContext);
}

void Controller::render(Utils::InternalId modelId) const
{
    const std::shared_ptr<Model::IItem> modelItem{ findItem(modelId) };

    const GPU::Context gpuContext{ modelItem->GPUContext() };
    glBindVertexArray(gpuContext.vertexArrayId);
    glDrawArrays(GL_TRIANGLES, 0, modelItem->verticesCount());
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}
} // namespace Model
