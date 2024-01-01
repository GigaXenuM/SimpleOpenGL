#pragma once

#include "iitem.h"
#include "GPU-tools/gpucontext.h"

namespace Model
{
class Mesh;

class Item : public IItem
{
public:
    explicit Item(std::shared_ptr<Model::Mesh> mesh);

    std::shared_ptr<Model::Mesh> mesh() const override;

    GPU::Context GPUContext() const override;
    void setGPUContext(GPU::Context context) override;

    unsigned int verticesCount() const override;

private:
    std::shared_ptr<Model::Mesh> _mesh;
    GPU::Context _gpuContext;
};
} // namespace Model
