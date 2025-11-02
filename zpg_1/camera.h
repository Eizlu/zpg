#pragma once
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/fwd.hpp>
#include <vector>
#include "subject.h"

class Camera : public Subject
{
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	
	glm::mat4 projectionMatrix;
	float aspectRatio;
	float fov;
	float nearPlane;
	float farPlane;


	float movementSpeed;
	float yaw, pitch;
	float mouseSensitivity;

	void updateProjectionMatrix();
public:
	Camera();
	Camera(int screenWidth, int screenHeight);
	~Camera()=default;
	glm::mat4 LookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up) const;

	glm::vec3 getPosition() const;
	glm::vec3 getFront() const;
	glm::vec3 getUp() const;
	glm::vec3 getRight() const;
	glm::mat4 getProjectionMatrix() const;
	void updateVector();

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void setMovementSpeed(float speed);

	void updateAspectRatio(int width, int height);
	void setFOV(float newFov);

	//mys
	void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
	void setMouseSensitivity(float sensitivity);
};

