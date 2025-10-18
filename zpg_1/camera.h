#pragma once
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <vector>
#include "cameraObserver.h"

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	//glm::mat4 viewMatrix;
	//glm::mat4 projectionMatrix;

	float movementSpeed;
	float yaw, pitch;
	float mouseSensitivity;

	std::vector<CameraObserver*> observers;

public:
	Camera();
	~Camera()=default;
	glm::mat4 LookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up) const;

	glm::vec3 getPosition() const;
	glm::vec3 getFront() const;
	glm::vec3 getUp() const;
	glm::vec3 getRight() const;
	void updateVector();

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void setMovementSpeed(float speed);

	//mys
	void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
	void setMouseSensitivity(float sensitivity);

	void addObserver(CameraObserver* observer);
	void removeObserver(CameraObserver* observer);
	void notifyObservers();

};

