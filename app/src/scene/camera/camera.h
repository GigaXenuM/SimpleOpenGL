#pragma once

#include "scene/eventhandler.h"

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
    void handleEvent(Event *event) override;

    void keyPressEvent(KeyPressEvent *event);
    void keyReleaseEvent(KeyReleaseEvent *event);
    void mouseMoveEvent(MouseMoveEvent *event);

    void update();

private:
    void updateDirection();
    void updateView();

    double _fov;
    double _aspectRatio;
    double _renderDistance;

    glm::vec3 _position;
    glm::vec3 _direction;
    glm::vec3 _cameraFront;

    glm::vec3 _up;
    glm::vec3 _cameraRight;
    glm::vec3 _cameraUp;

    glm::mat4 _projection;
    glm::mat4 _view;
};
} // namespace Scene
