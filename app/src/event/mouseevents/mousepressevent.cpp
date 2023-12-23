#include "mousepressevent.h"

MousePressEvent::MousePressEvent(Mouse::Button button, glm::vec2 position)
    : MouseActionEvent{ button, position }
{
}
