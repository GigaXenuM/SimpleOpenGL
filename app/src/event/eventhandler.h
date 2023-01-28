#pragma once

class Event;

namespace Scene
{
class EventHandler
{
public:
    virtual ~EventHandler() = default;

    virtual void handleEvent(Event *event) = 0;
};
} // namespace Scene
