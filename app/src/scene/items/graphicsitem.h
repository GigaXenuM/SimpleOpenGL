#pragma once

#include "iitem.h"

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

private:
    std::shared_ptr<Model::ModelItem> _modelItem;
};
} // namespace Scene
