#include "keyreleaseevent.h"

KeyReleaseEvent::KeyReleaseEvent(Keyboard::Key key, Keyboard::Modifier modifier)
    : KeyActionEvent{ key, modifier }
{
}
