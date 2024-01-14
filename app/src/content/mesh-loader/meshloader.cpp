#include "meshloader.h"
#include "model/vertex.h"
#include "model/mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <ostream>

namespace Content
{

std::vector<std::shared_ptr<Model::Mesh>> MeshLoader::load(std::string path)
{
    Assimp::Importer importer;

    // Specify post-processing options (such as triangulation, flipping UV coordinates, etc.)
    unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs;

    // Load the model
    const aiScene *scene = importer.ReadFile(path.c_str(), flags);

    // Check if the import was successful
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "Error loading model: " << importer.GetErrorString() << std::endl;
    }

    std::vector<std::shared_ptr<Model::Mesh>> meshes;

    // process each mesh located at the current node
    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[i];
        meshes.push_back(processMesh(mesh));
    }

    return meshes;
}

std::shared_ptr<Model::Mesh> MeshLoader::processMesh(aiMesh *mesh)
{
    // data to fill
    std::vector<Model::Vertex> vertices;
    std::vector<unsigned int> indices;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Model::Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class
                          // that doesn't directly convert to glm's vec3 class so we transfer the
                          // data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the
            // assumption that we won't use models where a vertex can have multiple texture
            // coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texturePosition = vec;
        }

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the
    // corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    return std::make_shared<Model::Mesh>(std::move(vertices), std::move(indices));
}
} // namespace Content
