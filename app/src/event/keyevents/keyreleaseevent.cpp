#include "keyreleaseevent.h"

KeyReleaseEvent::KeyReleaseEvent(Keyboard::Key key, Keyboard::Modifier modifier)
    : _key{ key }, _modifier{ modifier }
{
}

Keyboard::Key KeyReleaseEvent::key() const
{
    return _key;
}

Keyboard::Modifier KeyReleaseEvent::modifier() const
{
    return _modifier;
}
