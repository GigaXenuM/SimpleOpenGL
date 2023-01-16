#pragma once

#include "texturetype.h"

#include <string>

namespace Tools
{

struct Texture
{
    unsigned int id;
    TextureType type;
    std::string path;
};
} // namespace Tools
