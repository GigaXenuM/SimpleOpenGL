#pragma once

namespace GPU
{
struct Context
{
    unsigned int vertexBufferId{ 0 };
    unsigned int vertexArrayId{ 0 };
    unsigned int elementBufferId{ 0 };
    unsigned int indicesSize{ 0 };
};
} // namespace GPU
