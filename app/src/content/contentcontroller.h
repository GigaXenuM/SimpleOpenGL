#pragma once

#include <memory>
#include <unordered_map>

namespace Model
{
class Controller;
} // namespace Model

namespace Scene
{
class Controller;
}

namespace GPU
{
enum class ShaderType;
class IProgram;
} // namespace GPU

namespace Content
{
class Controller
{
    using ShaderProgramMap = std::unordered_map<GPU::ShaderType, std::shared_ptr<GPU::IProgram>>;

public:
    Controller(int width, int height);

    void render() const;

    std::shared_ptr<Model::Controller> modelController() const;
    std::shared_ptr<Scene::Controller> sceneController() const;

private:
    static std::shared_ptr<GPU::IProgram> createShaderProgram(const char *vertexShaderSource,
                                                              const char *fragmentShaderSource);
    static ShaderProgramMap shaderProgramMap();

    static std::vector<std::string> modelPathes();

    void createContent();
    void loadModels();

    std::shared_ptr<Model::Controller> _modelController;
    std::shared_ptr<Scene::Controller> _sceneController;
};
} // namespace Content
