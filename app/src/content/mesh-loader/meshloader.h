#pragma once

#include <memory>
#include <string>
#include <vector>

class aiMesh;

namespace Model
{
class Mesh;
} // namespace Model

namespace Content
{
class MeshLoader
{
public:
    static std::vector<std::shared_ptr<Model::Mesh>> load(std::string path);

private:
    static std::shared_ptr<Model::Mesh> processMesh(aiMesh *mesh);
};
} // namespace Content
