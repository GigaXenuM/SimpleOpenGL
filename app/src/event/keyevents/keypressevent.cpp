#include "keypressevent.h"

KeyPressEvent::KeyPressEvent(Keyboard::Key key, Keyboard::Modifier modifier)
    : _key{ key }, _modifier{ modifier }
{
}

Keyboard::Key KeyPressEvent::key() const
{
    return _key;
}

Keyboard::Modifier KeyPressEvent::modifier() const
{
    return _modifier;
}
