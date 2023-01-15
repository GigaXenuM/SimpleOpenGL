#pragma once

#include "tools/texture.h"
#include "scene/mesh/mesh.h"

#include <assimp/material.h>

#include <vector>
#include <string>

class aiNode;
class aiScene;
class aiMesh;

class ModelLoader
{
public:
    explicit ModelLoader(const std::string &path);

    void draw(unsigned int programId) const;

private:
    void loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene);

    Scene::Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                              std::string typeName);

    unsigned int TextureFromFile(const char *path, const std::string &directory);

    std::vector<Tools::Texture> _texturesLoaded;
    std::vector<Scene::Mesh> _meshes;
    std::string _directory;
};
