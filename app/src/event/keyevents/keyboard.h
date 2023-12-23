#pragma once

#include "GLFW/glfw3.h"

namespace Keyboard
{

enum class Key
{
    A = GLFW_KEY_A,
    D = GLFW_KEY_D,
    S = GLFW_KEY_S,
    W = GLFW_KEY_W,
    Left = GLFW_KEY_LEFT,
    Right = GLFW_KEY_RIGHT,
    Up = GLFW_KEY_UP,
    Down = GLFW_KEY_DOWN,
    Space = GLFW_KEY_SPACE,
    Escape = GLFW_KEY_ESCAPE,

    MAX_SIZE = GLFW_KEY_LAST
};

enum class Modifier
{
    None = 0x0,
    Shift = GLFW_MOD_SHIFT,
    Control = GLFW_MOD_CONTROL,
    Alt = GLFW_MOD_ALT,
    Super = GLFW_MOD_SHIFT,
    CapsLock = GLFW_MOD_CAPS_LOCK,
    NumLock = GLFW_MOD_NUM_LOCK
};

inline Modifier operator|(Modifier a, Modifier b)
{
    return static_cast<Modifier>(static_cast<int>(a) | static_cast<int>(b));
}

inline Modifier operator&(Modifier a, Modifier b)
{
    return static_cast<Modifier>(static_cast<int>(a) & static_cast<int>(b));
}

inline Modifier &operator|=(Modifier &a, Modifier b)
{
    return a = a | b;
}
} // namespace Keyboard
