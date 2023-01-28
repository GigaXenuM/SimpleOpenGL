#pragma once

#include "event/event.h"

#include "event/keyevents/keyboard.h"

class KeyPressEvent : public Event
{
public:
    explicit KeyPressEvent(Keyboard::Key key, Keyboard::Modifier modifier);

    EventType type() const override
    {
        return EventType::KEY_PRESS;
    }

    Keyboard::Key key() const;
    Keyboard::Modifier modifier() const;

private:
    Keyboard::Key _key;
    Keyboard::Modifier _modifier;
};
