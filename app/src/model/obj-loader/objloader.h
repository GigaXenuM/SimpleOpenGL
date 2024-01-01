#pragma once

#include <memory>
#include <string>

namespace Model
{
class Mesh;

namespace OBJ
{
enum class DataType;
} // namespace OBJ

namespace OBJLoader
{
std::shared_ptr<Mesh> load(const char *path);

OBJ::DataType dataType(std::string prefix);

}; // namespace OBJLoader
}; // namespace Model
