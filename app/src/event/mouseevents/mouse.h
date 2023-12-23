#pragma once

#include <GLFW/glfw3.h>

namespace Mouse
{
enum class Button : unsigned long long
{
    Left = GLFW_MOUSE_BUTTON_LEFT,
    Right = GLFW_MOUSE_BUTTON_RIGHT,
    Middle = GLFW_MOUSE_BUTTON_MIDDLE,

    MAX_SIZE = GLFW_MOUSE_BUTTON_LAST
};
}
