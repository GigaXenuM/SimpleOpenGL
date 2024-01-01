#include "application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "event/keyevents/keypressevent.h"
#include "event/keyevents/keyreleaseevent.h"
#include "event/mouseevents/mousemoveevent.h"
#include "mainwindow.h"

glm::vec2 LAST_MOUSE_POS{ 0, 0 };

void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void cursorPosCallback(GLFWwindow *window, double x, double y);

Application::Application() : _window{ &MainWindow::instance() }
{
    _window->setBackgroundColor({ 0.3f, 0.3f, 0.3f, 1.0f });
}

Application::~Application()
{
    glfwTerminate();
}

int Application::run()
{
    GLFWwindow *glfwWindow{ _window->getGLFWWindow() };

    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    defineCursorPos(glfwWindow);

    glfwSetCursorPosCallback(glfwWindow, cursorPosCallback);
    glfwSetKeyCallback(glfwWindow, keyboardCallback);

    while (!glfwWindowShouldClose(glfwWindow))
    {
        _window->render();

        glfwSwapBuffers(glfwWindow);

        glfwPollEvents();
    }

    return 0;
}

void Application::defineCursorPos(GLFWwindow *window)
{
    double x{ 0 }, y{ 0 };
    glfwGetCursorPos(window, &x, &y);
    LAST_MOUSE_POS = { x, y };
}

void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    MainWindow *handle{ static_cast<MainWindow *>(glfwGetWindowUserPointer(window)) };

    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, true);

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

    const glm::vec2 currentMousePos{ x, y };
    MouseMoveEvent event(currentMousePos, LAST_MOUSE_POS);
    handle->handleEvent(&event);

    LAST_MOUSE_POS = currentMousePos;
}
