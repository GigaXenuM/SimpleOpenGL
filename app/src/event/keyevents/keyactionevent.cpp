#include "keyactionevent.h"

KeyActionEvent::KeyActionEvent(Keyboard::Key key, Keyboard::Modifier modifier)
    : _key{ key }, _modifier{ modifier }
{
}

Keyboard::Key KeyActionEvent::key() const
{
    return _key;
}

Keyboard::Modifier KeyActionEvent::modifier() const
{
    return _modifier;
}
