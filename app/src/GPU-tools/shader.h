#pragma once

#include "igpuidentifier.h"

namespace GPU
{
class Shader : public IGPUIdentifier
{
public:
    explicit Shader(const char *pathToSource, unsigned int shaderType);

    unsigned int id() const override;

private:
    unsigned int compile(const char *pathToSource, unsigned int shaderType);

    unsigned int _shaderId;
};
} // namespace GPU
