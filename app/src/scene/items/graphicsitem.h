#pragma once

#include "iitem.h"

#include <glm/glm.hpp>

#include <memory>

namespace Model
{
class ModelItem;
}

namespace Scene
{

class GraphicsItem : public IItem
{
public:
    GraphicsItem(std::shared_ptr<Model::ModelItem> modelItem);

    void draw(unsigned int programId) const override;

    void setModel(glm::mat4 model);
    const glm::mat4 &model() const override;

private:
    std::shared_ptr<Model::ModelItem> _modelItem;
    glm::mat4 _model;
};
} // namespace Scene
