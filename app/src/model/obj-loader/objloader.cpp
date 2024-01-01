#include "objloader.h"

#include "utils/file-loader/fileloader.h"
#include "datatype.h"
#include "model/vertex.h"
#include "model/mesh.h"

#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

namespace Model
{

std::shared_ptr<Mesh> OBJLoader::load(const char *path)
{
    using OBJ::DataType;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texturePositions;
    std::vector<glm::vec3> normals;

    std::vector<unsigned int> positionIndices;
    std::vector<unsigned int> texturePositionIndices;
    std::vector<unsigned int> normalIndices;

    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cout << "ERROR: File " << path << " not opened.";
        return nullptr;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream stream{ line };
        std::string prefix;
        stream >> prefix;

        switch (dataType(prefix))
        {
        case DataType::Position:
        {
            glm::vec3 position;
            stream >> position.x >> position.y >> position.z;
            positions.push_back(position);
            break;
        }
        case DataType::TexturePosition:
        {
            glm::vec2 texturePosition;
            stream >> texturePosition.x >> texturePosition.y;
            texturePositions.push_back(texturePosition);
            break;
        }
        case DataType::Normal:
        {
            glm::vec3 normal;
            stream >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
            break;
        }
        case DataType::Face:
        {
            unsigned int counter{ 0 };
            unsigned int index{ 0 };

            bool hasDifferentIndices{ false };

            while (stream >> index)
            {
                if (counter == 0)
                    positionIndices.push_back(index);
                if (counter == 1)
                    texturePositionIndices.push_back(index);
                if (counter == 2)
                    normalIndices.push_back(index);

                const int nextSymbol{ stream.peek() };

                if (nextSymbol == '/')
                    hasDifferentIndices = true;
                if (nextSymbol == '/' || nextSymbol == ' ')
                {
                    counter = (counter >= 2) || (!hasDifferentIndices) ? 0 : counter + 1;
                    stream.ignore(1, nextSymbol);
                }
            }
            break;
        }
        case DataType::Undefined:
            break;
        }
    }

    file.close();

    std::vector<Vertex> vertices;
    const size_t indicesSize{ positionIndices.size() };
    vertices.resize(indicesSize, Vertex());
    for (size_t i = 0; i < indicesSize; ++i)
    {
        vertices[i].position = positions[positionIndices[i] - 1];
        if (!texturePositions.empty())
            vertices[i].texturePosition = texturePositions[texturePositionIndices[i] - 1];
        if (!normals.empty())
            vertices[i].normal = normals[normalIndices[i] - 1];
    }

    return std::make_shared<Mesh>(std::move(vertices));
}

OBJ::DataType OBJLoader::dataType(std::string prefix)
{
    using OBJ::DataType;
    std::unordered_map<std::string, DataType> prefixToType{ { "v", DataType::Position },
                                                            { "vt", DataType::TexturePosition },
                                                            { "vn", DataType::Normal },
                                                            { "f", DataType::Face } };

    const auto it = prefixToType.find(prefix);

    return it == prefixToType.cend() ? DataType::Undefined : prefixToType[prefix];
}

} // namespace Model
