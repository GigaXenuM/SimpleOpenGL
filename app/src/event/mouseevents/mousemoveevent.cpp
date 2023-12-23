#include "mousemoveevent.h"

MouseMoveEvent::MouseMoveEvent(glm::vec2 pos, glm::vec2 lastPos) : _pos{ pos }, _lastPos{ lastPos }
{
}

glm::vec2 MouseMoveEvent::position() const
{
    return _pos;
}

glm::vec2 MouseMoveEvent::lastPosition() const
{
    return _lastPos;
}
