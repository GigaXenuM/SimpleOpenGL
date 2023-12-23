#pragma once

#include "event/event.h"

#include <glm/vec2.hpp>

class MouseMoveEvent : public Event
{
public:
    explicit MouseMoveEvent(glm::vec2 pos, glm::vec2 lastPos);

    EventType type() const override
    {
        return EventType::MOUSE_MOVE;
    }

    glm::vec2 position() const;
    glm::vec2 lastPosition() const;

private:
    glm::vec2 _pos;
    glm::vec2 _lastPos;
};
