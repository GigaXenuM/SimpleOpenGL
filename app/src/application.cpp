#include "application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "mainwindow.h"

#include "tools/color.h"

Application::Application(MainWindow *window) : _window{ window }
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

    /* Loop until the user closes the window */
    while (!_window->shouldClose())
    {
        _window->draw();

        _window->swapBuffers();

        glfwPollEvents();
    }

    return 0;
}
