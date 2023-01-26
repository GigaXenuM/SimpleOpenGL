#include "application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "event/keyevents/keypressevent.h"
#include "event/keyevents/keyreleaseevent.h"
#include "event/mouseevents/mousemoveevent.h"
#include "mainwindow.h"

#include "tools/color.h"

void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void cursorPosCallback(GLFWwindow *window, double x, double y);

Application::Application() : _window{ &MainWindow::instance() }
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window->setBackgroundColor({ 0.3f, 0.3f, 0.3f, 1.0f });
}

Application::~Application()
{
    glfwTerminate();
}

int Application::run()
{
    _window->init();
    GLFWwindow *glfwWindow{ _window->getGLFWWindow() };

    glfwSetCursorPosCallback(glfwWindow, cursorPosCallback);
    glfwSetKeyCallback(glfwWindow, keyboardCallback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(glfwWindow))
    {
        _window->draw();

        glfwSwapBuffers(glfwWindow);

        glfwPollEvents();
    }

    return 0;
}

void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    MainWindow *handle{ static_cast<MainWindow *>(glfwGetWindowUserPointer(window)) };

    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        KeyPressEvent event(Keyboard::Key{ key }, Keyboard::Modifier{ mods });
        handle->handleEvent(&event);
        return;
    }

    KeyReleaseEvent event(Keyboard::Key{ key }, Keyboard::Modifier{ mods });
    handle->handleEvent(&event);
}

void cursorPosCallback(GLFWwindow *window, double x, double y)
{
    MainWindow *handle{ static_cast<MainWindow *>(glfwGetWindowUserPointer(window)) };

    MouseMoveEvent event(x, y);
    handle->handleEvent(&event);
}
