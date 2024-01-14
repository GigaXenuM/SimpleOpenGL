#pragma once

#include "GPU-tools/igpuidentifier.h"

#include <glm/glm.hpp>

#include <string>

namespace GPU
{
class IProgram : public IGPUIdentifier
{
public:
    virtual void use() const = 0;
    virtual void setMat4(const std::string &name, const glm::mat4 &mat) const = 0;
    virtual void setVec3(const std::string &name, const glm::vec3 &vec) const = 0;
};
} // namespace GPU
