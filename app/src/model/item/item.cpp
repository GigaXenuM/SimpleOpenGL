#include "item.h"

#include <glad/glad.h>

namespace Model
{
Item::Item(Meshes meshes) : _meshes{ std::move(meshes) }
{
}

const Item::Meshes &Item::meshes() const
{
    return _meshes;
}

std::vector<GPU::Context> Item::GPUContext() const
{
    return _gpuContext;
}

void Item::addGPUContext(GPU::Context contextUnit)
{
    _gpuContext.push_back(contextUnit);
}
} // namespace Model
