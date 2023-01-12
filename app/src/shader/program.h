#pragma once

#include "ishaderwrapper.h"

#include <vector>

namespace GraphicsShader
{

class Program : public IShaderWrapper
{
public:
    explicit Program(unsigned int firstShaderId, unsigned int secondShaderId);

    unsigned int id() const override;

private:
    unsigned int link(unsigned int firstShaderId, unsigned int secondShaderId);

    unsigned int _id;
};
} // namespace GraphicsShader
