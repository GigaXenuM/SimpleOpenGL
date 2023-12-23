#pragma once

#include "event/keyevents/keyactionevent.h"

class KeyPressEvent : public KeyActionEvent
{
public:
    explicit KeyPressEvent(Keyboard::Key key, Keyboard::Modifier modifier);

    EventType type() const override
    {
        return EventType::KEY_PRESS;
    }
};
