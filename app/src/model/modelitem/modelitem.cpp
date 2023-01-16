#include "modelitem.h"

#include "tools/stb_image.h"
#include "tools/texturetype.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <glad/glad.h>

#include <iostream>

Model::ModelItem::ModelItem(const std::string &path) : _path{ path }
{
}

Model::ModelItem::~ModelItem()
{
    for (auto *mesh : _meshes)
        delete mesh;
}

const std::vector<Scene::Mesh *> &Model::ModelItem::meshes() const
{
    return _meshes;
}

void Model::ModelItem::loadModel()
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(_path, aiProcess_Triangulate | aiProcess_FlipUVs
                                                        | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    _directory = _path.substr(0, _path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::ModelItem::processNode(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Scene::Mesh *Model::ModelItem::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;

        // Coords
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        // Normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;

        // Texture coords
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        }

        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.tangent = vector;

        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.bitangent = vector;
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<Texture> diffuseMaps
        = loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::Diffuse);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<Texture> specularMaps
        = loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::Specular);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<Texture> normalMaps
        = loadMaterialTextures(material, aiTextureType_HEIGHT, TextureType::Normal);
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<Texture> heightMaps
        = loadMaterialTextures(material, aiTextureType_AMBIENT, TextureType::Ambient);
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return new Scene::Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::ModelItem::loadMaterialTextures(aiMaterial *material,
                                                            aiTextureType aiType, TextureType type)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < material->GetTextureCount(aiType); i++)
    {
        aiString str;
        material->GetTexture(aiType, i, &str);

        bool skip = false;
        for (const auto &texture : _texturesLoaded)
        {
            if (std::strcmp(texture.path.data(), str.C_Str()) == 0)
            {
                textures.push_back(texture);
                continue;
            }
        }

        Texture texture;
        texture.id = TextureFromFile(str.C_Str(), _directory);
        texture.type = type;
        texture.path = str.C_Str();
        textures.push_back(texture);
        _texturesLoaded.push_back(texture);
    }
    return textures;
}

unsigned int Model::ModelItem::TextureFromFile(const char *path, const std::string &directory)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format{ GL_RGB };
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << directory + '/' + path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
