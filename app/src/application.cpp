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

    _window->setBackgroundColor({ 0.3f, 0.7f, 0.4f, 1.0f });
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
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Color backgroundColor{ _window->backgroundColor() };
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

        _window->draw();

        _window->swapBuffers();

        glfwPollEvents();
    }

    return 0;
}
