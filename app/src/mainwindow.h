#pragma once

#include "tools/color.h"

class GLFWwindow;

class MainWindow
{
public:
    MainWindow(int width, int height, const char *title);
    ~MainWindow();

    int width();
    int height();

    int shouldClose();
    void swapBuffers();
    void makeContextCurrent();
    void create();

    Color backgroundColor();
    void setBackgroundColor(Color color);

private:
    GLFWwindow *_window{ nullptr };
    int _width{ 0 };
    int _height{ 0 };
    const char *_title{ nullptr };
    Color _backgroundColor;
};
