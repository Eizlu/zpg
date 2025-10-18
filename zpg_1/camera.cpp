#include "camera.h"
#include <glm/ext/matrix_transform.hpp>

Camera::Camera() :position(0.0f, 0.0f, 3.0f), front(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f), movementSpeed(0.1f)
{
	updateVector();
}

void Camera::updateVector()
{
	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, up));
	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::LookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up) const
{
	return glm::lookAt(eye, center, up);
}


glm::vec3 Camera::getPosition()
{
	return position;
}

glm::vec3 Camera::getFront()
{
	return front;
}

glm::vec3 Camera::getUp()
{
	return up;
}

void Camera::moveForward()
{
	position += movementSpeed * front;
}

void Camera::moveBackward()
{
	position -= movementSpeed * front;
}

void Camera::moveLeft()
{
	position -= movementSpeed * right;
}

void Camera::moveRight()
{
	position += movementSpeed * right;
}

void Camera::moveUp()
{
	position += movementSpeed * up;
}

void Camera::moveDown()
{
	position -= movementSpeed * up;
}

void Camera::setMovementSpeed(float speed)
{
	movementSpeed = speed;
}