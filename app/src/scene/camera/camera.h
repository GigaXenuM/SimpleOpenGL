#pragma once

#include "event/eventhandler.h"

#include "event/keyevents/keyboard.h"

#include <glm/glm.hpp>

class KeyPressEvent;
class KeyReleaseEvent;
class MouseMoveEvent;

namespace Scene
{

class Camera : public EventHandler
{

public:
    explicit Camera(double fov, double aspectRatio, double renderDistance);

    void setPosition(const glm::vec3 &position);
    const glm::vec3 &position() const;

    void setDirection(const glm::vec3 &direction);
    const glm::vec3 &direction() const;

    const glm::mat4 &projection() const;
    const glm::mat4 &view() const;

    // EventHandler interface
    void keyPressEvent(KeyPressEvent *event) override;
    void keyReleaseEvent(KeyReleaseEvent *event) override;
    void mouseMoveEvent(MouseMoveEvent *event) override;

    void update();

private:
    void updateDirection();
    void updateView();

    void move();
    void lookAt();

    void calculateRendererTime();

    void processKey(Keyboard::Key key, bool pressed);

    double _fov;
    double _aspectRatio;
    double _renderDistance;

    glm::vec3 _position;
    glm::vec3 _direction;

    glm::vec3 _up;
    glm::vec3 _cameraRight;
    glm::vec3 _cameraUp;

    glm::mat4 _projection;
    glm::mat4 _view;

    bool _moveFront{ false };
    bool _moveBack{ false };
    bool _moveLeft{ false };
    bool _moveRight{ false };

    float _deltaTime{ 0.0f };
    float _lastFrame{ 0.0f };

    double _yaw{ -90.0f };
    double _pitch{ 0.0f };
};
} // namespace Scene
