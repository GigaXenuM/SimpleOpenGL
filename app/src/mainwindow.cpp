#include "mainwindow.h"

#include "shader/shader.h"
#include "shader/program.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include <iostream>

MainWindow::MainWindow(int width, int height, const char *title)
    : _window{ nullptr },
      _width{ width },
      _height{ height },
      _title{ title },
      _backgroundColor{ .0f, .0f, .0f, .0f }
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

    GLfloat vertices[] = {
        0.5f,  0.5f,  0.0f, // top right
        0.5f,  -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f  // top left
    };
    GLuint indices[] = { 0, 1, 3, 1, 2, 3 };

    Shader vertexShader("resources/vertex.glsl", GL_VERTEX_SHADER);
    Shader fragmentShader("resources/fragment.glsl", GL_FRAGMENT_SHADER);

    GraphicsShader::Program shaderProgram(vertexShader.id(), fragmentShader.id());
    _shaderProgram = shaderProgram.id();

    glGenBuffers(1, &_EBO);

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void MainWindow::draw()
{
    glUseProgram(_shaderProgram);
    glBindVertexArray(_VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

Color MainWindow::backgroundColor() const
{
    return _backgroundColor;
}

void MainWindow::setBackgroundColor(const Color &color)
{
    _backgroundColor = color;
}
