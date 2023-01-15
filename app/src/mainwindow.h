#pragma once

#include "tools/color.h"

class GLFWwindow;

namespace Scene
{
class Scene;
}

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

    void setBackgroundColor(const Tools::Color &color);

private:
    void prepareForDrawing();

    GLFWwindow *_window{ nullptr };
    Scene::Scene *_scene{ nullptr };

    int _width{ 0 };
    int _height{ 0 };
    const char *_title{ nullptr };
    Tools::Color _backgroundColor;
};
