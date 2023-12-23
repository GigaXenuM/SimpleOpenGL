#pragma once

#include "event/mouseevents/mouseactionevent.h"

class MousePressEvent : public MouseActionEvent
{
public:
    MousePressEvent(Mouse::Button button, glm::vec2 position);

    EventType type() const override
    {
        return EventType::MOUSE_PRESS;
    }
};
