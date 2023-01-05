#include "mainwindow.h"

#include <GLFW/glfw3.h>

MainWindow::MainWindow(int width, int height, const char *title)
    : _window{ nullptr },
      _width{ width },
      _height{ height },
      _title{ title },
      _backgroundColor{ .0f, .0f, .0f, 1.0f }
{
}

MainWindow::~MainWindow()
{
    glfwDestroyWindow(_window);
}

int MainWindow::width()
{
    return _width;
}

int MainWindow::height()
{
    return _height;
}

int MainWindow::shouldClose()
{
    return glfwWindowShouldClose(_window);
}

void MainWindow::swapBuffers()
{
    glfwSwapBuffers(_window);
}

void MainWindow::makeContextCurrent()
{
    glfwMakeContextCurrent(_window);
}

void MainWindow::create()
{
    _window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
}

Color MainWindow::backgroundColor()
{
    return _backgroundColor;
}

void MainWindow::setBackgroundColor(Color color)
{
    _backgroundColor = color;
}
