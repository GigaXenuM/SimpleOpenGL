#pragma once

#include "iitem.h"

#include "utils/internal-id/internalid.h"
#include "GPU-tools/shadertype.h"

#include <glm/glm.hpp>

namespace Scene
{

class GraphicsItem : public IItem
{
public:
    GraphicsItem(Utils::InternalId modelId, glm::mat4 model3D, GPU::ShaderType shaderType);

    Utils::InternalId modelId() const override;
    const glm::mat4 &model3D() const override;
    GPU::ShaderType shaderType() const override;

private:
    Utils::InternalId _modelId;
    glm::mat4 _model3D;
    GPU::ShaderType _shaderType{ GPU::ShaderType::Common };
};
} // namespace Scene
