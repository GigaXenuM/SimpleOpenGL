#pragma once

#include "utils/internal-id/internalid.h"

#include <unordered_map>
#include <memory>

namespace Model
{
class Mesh;
class IItem;

class Controller
{
    using ItemMap = std::unordered_map<Utils::InternalId, std::shared_ptr<IItem>>;

public:
    Controller();

    Utils::InternalId createModelItem(std::shared_ptr<Model::Mesh> mesh);

    void loadOnGPU(Utils::InternalId modelId);

    void render(Utils::InternalId modelId) const;

private:
    std::shared_ptr<IItem> findItem(Utils::InternalId modelId) const;

    ItemMap _itemMap;
    std::vector<Utils::InternalId> _itemIdsOnGPU;
};
} // namespace Model
