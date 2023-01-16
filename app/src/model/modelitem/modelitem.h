#pragma once

#include "tools/texture.h"
#include "model/mesh/mesh.h"

#include <assimp/material.h>

#include <vector>
#include <string>

class aiNode;
class aiScene;
class aiMesh;

namespace Model
{

class ModelItem
{
public:
    explicit ModelItem(const std::string &path);
    ~ModelItem();

    void loadModel();

    const std::vector<Scene::Mesh *> &meshes() const;

private:
    void processNode(aiNode *node, const aiScene *scene);
    Scene::Mesh *processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType aiType,
                                              TextureType type);
    unsigned int TextureFromFile(const char *path, const std::string &directory);

    std::vector<Scene::Mesh *> _meshes;

    std::vector<Tools::Texture> _texturesLoaded;
    std::string _directory;
    std::string _path;
};
} // namespace Model
