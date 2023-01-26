#pragma once

#include "event/event.h"

#include "keyboard/keyboard.h"

class KeyReleaseEvent : public Event
{
public:
    explicit KeyReleaseEvent(Keyboard::Key key, Keyboard::Modifier modifier);

    EventType type() const override
    {
        return EventType::KEY_RELEASE;
    }

    Keyboard::Key key() const;
    Keyboard::Modifier modifier() const;

private:
    Keyboard::Key _key;
    Keyboard::Modifier _modifier;
};
