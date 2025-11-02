#include "camera.h"
#include <glm/ext/matrix_transform.hpp>
#include <algorithm>
#include <glm/ext/matrix_clip_space.hpp>

Camera::Camera() :
	position(0.0f, 0.0f, 3.0f), 
	front(0.0f, 0.0f, -1.0f), 
	up(0.0f, 1.0f, 0.0f), 
	movementSpeed(0.1f), 
	worldUp(0.0f, 1.0f, 0.0f),
	yaw(-90.0f), 
	pitch(0.0f), 
	mouseSensitivity(0.1f),
	aspectRatio(16.0f / 9.0f), 
	fov(45.0f),
	nearPlane(0.1f),
	farPlane(100.0f)
{
	updateVector();
	updateProjectionMatrix();
}

Camera::Camera(int screenWidth, int screenHeight) :
	position(0.0f, 0.0f, 3.0f),
	front(0.0f, 0.0f, -1.0f),
	up(0.0f, 1.0f, 0.0f),
	movementSpeed(0.1f),
	worldUp(0.0f, 1.0f, 0.0f),
	yaw(-90.0f),
	pitch(0.0f),
	mouseSensitivity(0.1f),
	fov(45.0f),
	nearPlane(0.1f),
	farPlane(100.0f)
{
	updateAspectRatio(screenWidth, screenHeight); 
	updateVector();
}

void Camera::updateProjectionMatrix()
{
	projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
	notifyObservers(); 
}

void Camera::updateAspectRatio(int width, int height)
{
	aspectRatio = (float)width / (float)height;
	updateProjectionMatrix();
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return projectionMatrix;
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

void Camera::setFOV(float newFov)
{
	fov = newFov;
	updateProjectionMatrix();
}