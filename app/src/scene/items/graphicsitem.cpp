#include "graphicsitem.h"

Scene::GraphicsItem::GraphicsItem(Utils::InternalId modelId, glm::mat4 model3D,
                                  GPU::ShaderType shaderType)
    : _modelId{ modelId }, _model3D{ model3D }, _shaderType{ shaderType }
{
}

Utils::InternalId Scene::GraphicsItem::modelId() const
{
    return _modelId;
}

const glm::mat4 &Scene::GraphicsItem::model3D() const
{
    return _model3D;
}

GPU::ShaderType Scene::GraphicsItem::shaderType() const
{
    return _shaderType;
}
