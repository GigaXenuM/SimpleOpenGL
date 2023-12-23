#pragma once

#include "event/eventhandler.h"

#include <vector>

class Event;

namespace Private::Scene
{

class SceneImpl : public EventHandler
{
protected:
    SceneImpl() = default;
    virtual ~SceneImpl() = default;

public:
    void addEventHandler(EventHandler *handler);
    virtual void handleEvent(Event *event) override;

private:
    std::vector<EventHandler *> _eventHandlers;
};
} // namespace Private::Scene
