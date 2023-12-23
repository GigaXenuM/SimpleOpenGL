#pragma once

#include "event/mouseevents/mouseactionevent.h"

class MouseReleaseEvent : public MouseActionEvent
{
public:
    MouseReleaseEvent(Mouse::Button button, glm::vec2 position);

    EventType type() const override
    {
        return EventType::MOUSE_RELEASE;
    }
};
