#pragma once

#include "event/eventhandler.h"

#include <glm/glm.hpp>

#include <memory>

class GLFWwindow;
class Event;

namespace Content
{
class Controller;
}

class MainWindow final : public EventHandler
{
public:
    static MainWindow &instance();

    int width() const;
    int height() const;

    void render();

    void setBackgroundColor(const glm::vec4 &color);

    __forceinline GLFWwindow *getGLFWWindow()
    {
        return _window;
    }

private:
    explicit MainWindow(int width, int height, const char *title);
    ~MainWindow();

    static GLFWwindow *init(int width, int height, const char *title);
    void prepareForDrawing();

    static MainWindow _instance;

    GLFWwindow *_window{ nullptr };
    std::shared_ptr<Content::Controller> _contentController;

    int _width{ 0 };
    int _height{ 0 };
    const char *_title{ nullptr };
    glm::vec4 _backgroundColor;
};
