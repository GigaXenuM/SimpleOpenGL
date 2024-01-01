#include "shadercontext.h"

#include <cassert>
#include <unordered_map>

namespace Content
{

ShaderContext shaderContextBy(GPU::ShaderType type)
{
    std::unordered_map<GPU::ShaderType, ShaderContext> typeToContext{
        { GPU::ShaderType::Common,
          { "resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl" } }
    };

    const auto it{ typeToContext.find(type) };
    assert(it != typeToContext.cend());

    return it->second;
}

} // namespace Content
