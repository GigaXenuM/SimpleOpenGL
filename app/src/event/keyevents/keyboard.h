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
    Space = GLFW_KEY_SPACE
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

enum class Actions
{
    Pressed = GLFW_PRESS,
    Released = GLFW_RELEASE
};
} // namespace Keyboard
