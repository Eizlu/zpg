#pragma once
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>


class Camera
{
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	//glm::mat4 viewMatrix;
	//glm::mat4 projectionMatrix;
	float movementSpeed;
public:
	Camera();
	~Camera()=default;
	glm::mat4 LookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up) const;

	glm::vec3 getPosition();
	glm::vec3 getFront();
	glm::vec3 getUp();
	void updateVector();

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void setMovementSpeed(float speed);

};