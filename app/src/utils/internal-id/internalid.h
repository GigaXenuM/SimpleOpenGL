#pragma once

#include <functional>

namespace Utils
{

class InternalId
{
public:
    static InternalId invalidId();

    InternalId();
    explicit InternalId(unsigned long long id);
    bool isValid() const;
    unsigned long long get() const;
    void setId(unsigned long long id);

private:
    explicit InternalId(unsigned long long id, bool valid);

    static unsigned long long idCounter;
    static unsigned long long createId();

    unsigned long long _id;
    bool _isValid{ true };
};

bool operator==(const Utils::InternalId &lhs, const Utils::InternalId &rhs);
bool operator!=(const Utils::InternalId &lhs, const Utils::InternalId &rhs);
bool operator<(const Utils::InternalId &lhs, const Utils::InternalId &rhs);

} // namespace Utils

namespace std
{
template <> struct hash<Utils::InternalId>
{
    size_t operator()(const Utils::InternalId &keyValue) const;
};
} // namespace std
