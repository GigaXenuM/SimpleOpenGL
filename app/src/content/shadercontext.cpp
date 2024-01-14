#include "shadercontext.h"

#include <cassert>
#include <unordered_map>

namespace Content
{

ShaderContext shaderContextBy(GPU::ShaderType type)
{
    std::unordered_map<GPU::ShaderType, ShaderContext> typeToContext{
        { GPU::ShaderType::Common,
          { "resources/shaders/common.vert", "resources/shaders/common.frag" } },
        { GPU::ShaderType::Lightning,
          { "resources/shaders/common.vert", "resources/shaders/lightning.frag" } }
    };

    const auto it{ typeToContext.find(type) };
    assert(it != typeToContext.cend());

    return it->second;
}

} // namespace Content
