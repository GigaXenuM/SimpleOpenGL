#pragma once

#include <memory>
#include <vector>

namespace Model
{
class Mesh;
}

namespace GPU
{
struct Context;
}

namespace Model
{
class IItem
{
public:
    using Meshes = std::vector<std::shared_ptr<Model::Mesh>>;

    virtual const Meshes &meshes() const = 0;

    virtual std::vector<GPU::Context> GPUContext() const = 0;
    virtual void addGPUContext(GPU::Context context) = 0;
};
} // namespace Model
