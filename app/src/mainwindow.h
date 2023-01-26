#pragma once

#include "tools/color.h"

class GLFWwindow;
class Event;

namespace Scene
{
class Scene;
}

class MainWindow final
{
public:
    static MainWindow &instance();

    int width() const;
    int height() const;

    void init();
    void draw();

    void setBackgroundColor(const Tools::Color &color);

    void handleEvent(Event *event);

    __forceinline GLFWwindow *getGLFWWindow()
    {
        return _window;
    }

private:
    explicit MainWindow(int width, int height, const char *title);
    ~MainWindow();

    static MainWindow _instance;

    void prepareForDrawing();

    GLFWwindow *_window{ nullptr };
    Scene::Scene *_scene{ nullptr };

    int _width{ 0 };
    int _height{ 0 };
    const char *_title{ nullptr };
    Tools::Color _backgroundColor;
};
