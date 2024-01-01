#pragma once

#include <memory>

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
    virtual std::shared_ptr<Model::Mesh> mesh() const = 0;

    virtual GPU::Context GPUContext() const = 0;
    virtual void setGPUContext(GPU::Context context) = 0;

    virtual unsigned int verticesCount() const = 0;
};
} // namespace Model
