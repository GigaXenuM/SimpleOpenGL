#pragma once

#include "ishaderwrapper.h"

namespace Shader
{
class Shader : public IShaderWrapper
{
public:
    explicit Shader(const char *pathToSource, unsigned int shaderType);

    unsigned int id() const override;

private:
    unsigned int compile(const char *pathToSource, unsigned int shaderType);

    unsigned int _shaderId;
};
} // namespace Shader
