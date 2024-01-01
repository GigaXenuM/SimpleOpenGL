#include "internalid.h"

#include <limits>

namespace Utils
{

unsigned long long InternalId::idCounter = 0;

InternalId InternalId::invalidId()
{
    return InternalId{ std::numeric_limits<unsigned long long>::max(), false };
}

InternalId::InternalId() : _id{ createId() }
{
}

InternalId::InternalId(unsigned long long id) : _id{ id }
{
}

InternalId::InternalId(unsigned long long id, bool valid) : _id{ id }, _isValid{ valid }
{
}

bool InternalId::isValid() const
{
    return _isValid;
}

unsigned long long InternalId::get() const
{
    return _id;
}

void InternalId::setId(unsigned long long id)
{
    _id = id;
    _isValid = (id != invalidId().get());
}

unsigned long long InternalId::createId()
{
    return idCounter++;
}

bool operator==(const Utils::InternalId &lhs, const Utils::InternalId &rhs)
{
    return lhs.get() == rhs.get();
}

bool operator!=(const Utils::InternalId &lhs, const Utils::InternalId &rhs)
{
    return !operator==(lhs, rhs);
}

bool operator<(const Utils::InternalId &lhs, const Utils::InternalId &rhs)
{
    return lhs.get() < rhs.get();
}

} // namespace Utils

size_t std::hash<Utils::InternalId>::operator()(const Utils::InternalId &keyValue) const
{
    return std::hash<unsigned long long>()(keyValue.get());
}
