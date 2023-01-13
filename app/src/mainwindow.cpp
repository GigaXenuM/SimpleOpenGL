#include "mainwindow.h"

#include "scene/scene.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include <iostream>

MainWindow::MainWindow(int width, int height, const char *title)
    : _window{ nullptr },
      _width{ width },
      _height{ height },
      _title{ title },
      _backgroundColor{ .0f, .0f, .0f, .0f },
      _scene{ new Scene::Scene }
{
}

MainWindow::~MainWindow()
{
    glfwDestroyWindow(_window);
}

int MainWindow::width() const
{
    return _width;
}

int MainWindow::height() const
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

void MainWindow::init()
{
    _window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
    glfwMakeContextCurrent(_window);

    gladLoadGL();
    glViewport(0, 0, _width, _height);

    _scene->init();
}

void MainWindow::prepareForDrawing()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(_backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a);
}

void MainWindow::draw()
{
    prepareForDrawing();

    _scene->draw();
}

void MainWindow::setBackgroundColor(const Color &color)
{
    _backgroundColor = color;
}
