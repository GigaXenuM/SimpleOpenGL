#pragma once

#include "event/event.h"

#include "event/keyevents/keyboard.h"

class KeyActionEvent : public Event
{
public:
    explicit KeyActionEvent(Keyboard::Key key, Keyboard::Modifier modifier);

    Keyboard::Key key() const;
    Keyboard::Modifier modifier() const;

private:
    Keyboard::Key _key;
    Keyboard::Modifier _modifier{ Keyboard::Modifier::None };
};
