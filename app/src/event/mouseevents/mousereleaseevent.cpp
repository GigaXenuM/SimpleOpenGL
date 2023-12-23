#include "mousereleaseevent.h"

MouseReleaseEvent::MouseReleaseEvent(Mouse::Button button, glm::vec2 position)
    : MouseActionEvent{ button, position }
{
}
