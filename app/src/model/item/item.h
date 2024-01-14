#pragma once

#include "iitem.h"
#include "GPU-tools/gpucontext.h"

namespace Model
{
class Mesh;

class Item : public IItem
{
public:
    explicit Item(Meshes meshes);

    const Meshes &meshes() const override;

    std::vector<GPU::Context> GPUContext() const override;
    void addGPUContext(GPU::Context contextUnit) override;

private:
    Meshes _meshes;
    std::vector<GPU::Context> _gpuContext;
};
} // namespace Model
