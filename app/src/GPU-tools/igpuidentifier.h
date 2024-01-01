#pragma once

namespace GPU
{
class IGPUIdentifier
{
public:
    virtual unsigned int id() const = 0;
};
} // namespace GPU
