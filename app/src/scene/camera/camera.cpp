#include "camera.h"

#include "event/event.h"

#include "event/keyevents/keypressevent.h"
#include "event/keyevents/keyreleaseevent.h"
#include "event/mouseevents/mousemoveevent.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

Scene::Camera::Camera(double fov, double aspectRatio, double renderDistance)
    : _fov{ fov },
      _aspectRatio{ aspectRatio },
      _renderDistance{ renderDistance },
      _position{ 0.0 },
      _direction{ 0.0, 0.0, 0.0 },
      _up{ 0.0, 1.0, 0.0 },
      _projection{ glm::perspective(glm::radians(_fov), _aspectRatio, 0.1, _renderDistance) }
{
    update();
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
    processKey(event->key(), true);
}

void Scene::Camera::keyReleaseEvent(KeyReleaseEvent *event)
{
    processKey(event->key(), false);
}

void Scene::Camera::mouseMoveEvent(MouseMoveEvent *event)
{
    if (_firstMouse)
    {
        _lastMousePosX = event->x();
        _lastMousePosY = event->y();
        _firstMouse = false;
    }

    _yaw += (event->x() - _lastMousePosX) * 0.05f;
    _pitch -= (event->y() - _lastMousePosY) * 0.05f;
    _lastMousePosX = event->x();
    _lastMousePosY = event->y();

    if (_pitch > 89.0f)
        _pitch = 89.0f;
    if (_pitch < -89.0f)
        _pitch = -89.0f;
}

void Scene::Camera::update()
{
    calculateRendererTime();
    lookAt();
    move();

    _cameraRight = glm::normalize(glm::cross(_direction, _up));
    _cameraUp = glm::cross(_cameraRight, _direction);
    _view = glm::lookAt(_position, _position + _direction, _cameraUp);
}

void Scene::Camera::move()
{
    float cameraSpeed{ 5.0f * _deltaTime };

    if (_moveFront)
        _position += cameraSpeed * _direction;
    if (_moveBack)
        _position -= cameraSpeed * _direction;
    if (_moveRight)
        _position += glm::normalize(glm::cross(_direction, _cameraUp)) * cameraSpeed;
    if (_moveLeft)
        _position -= glm::normalize(glm::cross(_direction, _cameraUp)) * cameraSpeed;
}

void Scene::Camera::lookAt()
{
    _direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _direction.y = sin(glm::radians(_pitch));
    _direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _direction = glm::normalize(_direction);
}

void Scene::Camera::calculateRendererTime()
{
    float currentFrame = glfwGetTime();
    _deltaTime = currentFrame - _lastFrame;
    _lastFrame = currentFrame;
}

void Scene::Camera::processKey(Keyboard::Key key, bool pressed)
{
    if (key == Keyboard::Key::A)
        _moveLeft = pressed;
    if (key == Keyboard::Key::D)
        _moveRight = pressed;
    if (key == Keyboard::Key::W)
        _moveFront = pressed;
    if (key == Keyboard::Key::S)
        _moveBack = pressed;
}
