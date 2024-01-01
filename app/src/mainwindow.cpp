#include "mainwindow.h"

#include "scene/scenecontroller.h"
#include "content/contentcontroller.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

MainWindow MainWindow::_instance{ 1366, 768, "Window" };

MainWindow::MainWindow(int width, int height, const char *title)
    : _window{ init(width, height, title) },
      _width{ width },
      _height{ height },
      _title{ title },
      _backgroundColor{ .0f, .0f, .0f, .0f },
      _contentController{ std::make_shared<Content::Controller>(width, height) }
{
    glfwSetWindowUserPointer(_window, this);
    addEventHandler(_contentController->sceneController().get());
}

MainWindow::~MainWindow()
{
    glfwDestroyWindow(_window);
}

MainWindow &MainWindow::instance()
{
    return _instance;
}

int MainWindow::width() const
{
    return _width;
}

int MainWindow::height() const
{
    return _height;
}

GLFWwindow *MainWindow::init(int width, int height, const char *title)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    return window;
}

void MainWindow::prepareForDrawing()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(_backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a);
}

void MainWindow::render()
{
    prepareForDrawing();

    _contentController->render();
}

void MainWindow::setBackgroundColor(const glm::vec4 &color)
{
    _backgroundColor = color;
}
