#pragma once

#include "ishaderwrapper.h"

#include <glm/glm.hpp>

#include <string>

namespace Shader
{

class Program : public IShaderWrapper
{
public:
    explicit Program(unsigned int firstShaderId, unsigned int secondShaderId);

    unsigned int id() const override;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    unsigned int link(unsigned int firstShaderId, unsigned int secondShaderId);

    unsigned int _id;
};
} // namespace Shader
