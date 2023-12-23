#pragma once

#include "iapplication.h"

class MainWindow;

class GLFWwindow;

class Application : public IApplication
{
public:
    explicit Application();
    ~Application();

    int run() override;

private:
    static void defineCursorPos(GLFWwindow *window);

    MainWindow *_window;
};
