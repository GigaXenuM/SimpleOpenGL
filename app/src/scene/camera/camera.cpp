#include "camera.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

Scene::Camera::Camera(double fov, double aspectRatio, double renderDistance)
    : _fov{ fov },
      _aspectRatio{ aspectRatio },
      _renderDistance{ renderDistance },
      _position{ 0.0 },
      _cameraFront{ 0.0, 0.0, -1.0 },
      _direction{ glm::normalize(_position - _cameraFront) },
      _up{ 0.0, 1.0, 0.0 },
      _cameraRight{ glm::normalize(glm::cross(_up, _direction)) },
      _cameraUp{ glm::cross(_direction, _cameraRight) },
      _projection{ glm::perspective(glm::radians(_fov), _aspectRatio, 0.1, _renderDistance) },
      _view{ glm::lookAt(_position, _position + _cameraFront, _cameraUp) }
{
}

void Scene::Camera::setPosition(glm::vec3 position)
{
    _position = position;
    update();
}

glm::vec3 Scene::Camera::position()
{
    return _position;
}

glm::mat4 Scene::Camera::projection()
{
    return _projection;
}

glm::mat4 Scene::Camera::view()
{
    return _view;
}

void Scene::Camera::update()
{
    _direction = glm::normalize(_position - _cameraFront);
    _cameraRight = glm::normalize(glm::cross(_up, _direction));
    _cameraUp = glm::cross(_direction, _cameraRight);
    _view = glm::lookAt(_position, _position + _cameraFront, _cameraUp);
}
