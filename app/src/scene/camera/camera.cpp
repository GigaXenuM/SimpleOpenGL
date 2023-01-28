#include "camera.h"

#include "event/event.h"

#include "event/keyevents/keyboard.h"

#include "event/keyevents/keypressevent.h"
#include "event/keyevents/keyreleaseevent.h"
#include "event/mouseevents/mousemoveevent.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

#include <iostream>

Scene::Camera::Camera(double fov, double aspectRatio, double renderDistance)
    : _fov{ fov },
      _aspectRatio{ aspectRatio },
      _renderDistance{ renderDistance },
      _position{ 0.0 },
      _direction{ 0.0, 0.0, -1.0 },
      _cameraFront{ glm::normalize(_position - _direction) },
      _up{ 0.0, 1.0, 0.0 },
      _cameraRight{ glm::normalize(glm::cross(_up, _cameraFront)) },
      _cameraUp{ glm::cross(_cameraFront, _cameraRight) },
      _projection{ glm::perspective(glm::radians(_fov), _aspectRatio, 0.1, _renderDistance) },
      _view{ glm::lookAt(_position, _position + _direction, _cameraUp) }
{
}

void Scene::Camera::setPosition(const glm::vec3 &position)
{
    _position = position;
    update();
}

const glm::vec3 &Scene::Camera::position() const
{
    return _position;
}

void Scene::Camera::setDirection(const glm::vec3 &direction)
{
    _direction = glm::normalize(direction);
    update();
}

const glm::vec3 &Scene::Camera::direction() const
{
    return _direction;
}

const glm::mat4 &Scene::Camera::projection() const
{
    return _projection;
}

const glm::mat4 &Scene::Camera::view() const
{
    return _view;
}

void Scene::Camera::handleEvent(Event *event)
{
    switch (event->type())
    {
    case Event::EventType::KEY_PRESS:
        keyPressEvent(static_cast<KeyPressEvent *>(event));
        return;
    case Event::EventType::KEY_RELEASE:
        keyReleaseEvent(static_cast<KeyReleaseEvent *>(event));
        return;
    case Event::EventType::MOUSE_MOVE:
        mouseMoveEvent(static_cast<MouseMoveEvent *>(event));
        return;
    default:
        return;
    }
}

void Scene::Camera::keyPressEvent(KeyPressEvent *event)
{
}

void Scene::Camera::keyReleaseEvent(KeyReleaseEvent *event)
{
}

void Scene::Camera::mouseMoveEvent(MouseMoveEvent *event)
{
}

void Scene::Camera::update()
{
    _cameraFront = glm::normalize(_position - _direction);
    _cameraRight = glm::normalize(glm::cross(_up, _cameraFront));
    _cameraUp = glm::cross(_cameraFront, _cameraRight);
    _view = glm::lookAt(_position, _position + _direction, _cameraUp);
}
