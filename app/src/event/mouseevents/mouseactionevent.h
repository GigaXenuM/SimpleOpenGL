#pragma once

#include "event/event.h"

#include "event/mouseevents/mouse.h"

#include <glm/vec2.hpp>

class MouseActionEvent : public Event
{
public:
    MouseActionEvent(Mouse::Button button, glm::vec2 position);

    Mouse::Button button() const;
    glm::vec2 position() const;

private:
    Mouse::Button _button;
    glm::vec2 _position;
};
