#pragma once

#include <glm/glm.hpp>

namespace Utils
{
class InternalId;
} // namespace Utils

namespace GPU
{
enum class ShaderType;
}

namespace Scene
{
class IItem
{
public:
    virtual ~IItem() = default;

    virtual Utils::InternalId modelId() const = 0;
    virtual const glm::mat4 &model3D() const = 0;
    virtual GPU::ShaderType shaderType() const = 0;
};
} // namespace Scene
