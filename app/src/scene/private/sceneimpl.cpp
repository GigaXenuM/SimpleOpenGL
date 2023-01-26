#include "sceneimpl.h"

void Private::Scene::SceneImpl::addEventHandler(EventHandler *handler)
{
    _eventHandlers.push_back(handler);
}

void Private::Scene::SceneImpl::handleEvent(Event *event)
{
    for (auto *handler : _eventHandlers)
        handler->handleEvent(event);
}
