#pragma once

#include "GPU-tools/shadertype.h"

#include <string>

namespace Content
{
struct ShaderContext
{
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
};

ShaderContext shaderContextBy(GPU::ShaderType type);
} // namespace Content
