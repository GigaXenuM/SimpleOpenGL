#include "graphicsitem.h"

#include "model/modelitem/modelitem.h"
#include "model/mesh/mesh.h"

Scene::GraphicsItem::GraphicsItem(std::shared_ptr<Model::ModelItem> modelItem)
    : _modelItem{ modelItem }
{
}

void Scene::GraphicsItem::draw(unsigned int programId) const
{
    for (const auto &mesh : _modelItem->meshes())
        mesh->draw(programId);
}

void Scene::GraphicsItem::setModel(glm::mat4 model)
{
    _model = model;
}

const glm::mat4 &Scene::GraphicsItem::model() const
{
    return _model;
}
