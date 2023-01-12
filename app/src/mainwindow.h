#pragma once

#include "tools/color.h"

class GLFWwindow;

class MainWindow
{
public:
    explicit MainWindow(int width, int height, const char *title);
    ~MainWindow();

    int width() const;
    int height() const;

    int shouldClose();
    void swapBuffers();
    void init();
    void draw();

    Color backgroundColor() const;
    void setBackgroundColor(const Color &color);

private:
    GLFWwindow *_window{ nullptr };
    int _width{ 0 };
    int _height{ 0 };
    const char *_title{ nullptr };
    Color _backgroundColor;

    unsigned int _shaderProgram;
    unsigned int _EBO;
    unsigned int _VAO;
    unsigned int _VBO;
};
