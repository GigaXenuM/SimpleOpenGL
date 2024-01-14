#pragma once

#include "GPU-tools/iprogram.h"

#include <glm/glm.hpp>

#include <string>

namespace GPU
{
class Program : public IProgram
{
public:
    explicit Program(unsigned int firstShaderId, unsigned int secondShaderId);

    unsigned int id() const override;
    void use() const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const override;
    void setVec3(const std::string &name, const glm::vec3 &vec) const override;

private:
    unsigned int link(unsigned int firstShaderId, unsigned int secondShaderId);

    unsigned int _id;
};
} // namespace GPU
