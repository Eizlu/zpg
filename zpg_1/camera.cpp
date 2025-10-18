#include "camera.h"
#include <glm/ext/matrix_transform.hpp>
#include <algorithm>

Camera::Camera() :
	position(0.0f, 0.0f, 3.0f), 
	front(0.0f, 0.0f, -1.0f), 
	up(0.0f, 1.0f, 0.0f), 
	movementSpeed(0.1f), 
	worldUp(0.0f, 1.0f, 0.0f),
	yaw(-90.0f), 
	pitch(0.0f), 
	mouseSensitivity(0.1f)
{
	updateVector();
}

void Camera::updateVector()
{
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front = glm::normalize(newFront);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));

	notifyObservers();
}

void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;
	yaw += xOffset;
	pitch += yOffset;
	if (constrainPitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}
	updateVector();
}

glm::mat4 Camera::LookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up) const
{
	return glm::lookAt(eye, center, up);
}


glm::vec3 Camera::getPosition() const
{
	return position;
}

glm::vec3 Camera::getFront() const
{
	return front;
}

glm::vec3 Camera::getUp() const
{
	return up;
}

glm::vec3 Camera::getRight() const
{
	return right;
}

void Camera::moveForward()
{
	position += movementSpeed * front;
	notifyObservers();
}

void Camera::moveBackward()
{
	position -= movementSpeed * front;
	notifyObservers();
}

void Camera::moveLeft()
{
	position -= movementSpeed * right;
	notifyObservers();
}

void Camera::moveRight()
{
	position += movementSpeed * right;
	notifyObservers();
}

void Camera::moveUp()
{
	position += movementSpeed * up;
	notifyObservers();
}

void Camera::moveDown()
{
	position -= movementSpeed * up;
	notifyObservers();
}

void Camera::setMovementSpeed(float speed)
{
	movementSpeed = speed;
}

void Camera::setMouseSensitivity(float sensitivity)
{
	mouseSensitivity = sensitivity;
}

void Camera::addObserver(CameraObserver* observer)
{
	observers.push_back(observer);
}

void Camera::removeObserver(CameraObserver* observer)
{
	observers.erase(std::remove(observers.begin(), observers.end(), observer ), observers.end());
}

void Camera::notifyObservers()
{
	for (auto observer : observers) {
		observer->onCameraChanged(*this);
	}
}