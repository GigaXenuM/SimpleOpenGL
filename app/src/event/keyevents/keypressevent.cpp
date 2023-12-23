#include "keypressevent.h"

KeyPressEvent::KeyPressEvent(Keyboard::Key key, Keyboard::Modifier modifier)
    : KeyActionEvent{ key, modifier }
{
}
