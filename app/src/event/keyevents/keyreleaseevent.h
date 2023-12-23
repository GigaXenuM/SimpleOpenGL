#pragma once

#include "event/keyevents/keyactionevent.h"

class KeyReleaseEvent : public KeyActionEvent
{
public:
    explicit KeyReleaseEvent(Keyboard::Key key, Keyboard::Modifier modifier);

    EventType type() const override
    {
        return EventType::KEY_RELEASE;
    }
};
