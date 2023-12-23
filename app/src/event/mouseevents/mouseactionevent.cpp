#include "mouseactionevent.h"

MouseActionEvent::MouseActionEvent(Mouse::Button button, glm::vec2 position)
    : _button{ button }, _position{ position }
{
}

Mouse::Button MouseActionEvent::button() const
{
    return _button;
}

glm::vec2 MouseActionEvent::position() const
{
    return _position;
}
