#include "item.h"

#include "model/mesh.h"

#include <glad/glad.h>

Model::Item::Item(std::shared_ptr<Model::Mesh> mesh) : _mesh{ std::move(mesh) }
{
}

std::shared_ptr<Model::Mesh> Model::Item::mesh() const
{
    return _mesh;
}

GPU::Context Model::Item::GPUContext() const
{
    return _gpuContext;
}

void Model::Item::setGPUContext(GPU::Context context)
{
    _gpuContext = context;
}

unsigned int Model::Item::verticesCount() const
{
    return _mesh->verticesCount();
}
