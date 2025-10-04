#pragma once
#include <GL/glew.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transformation
{
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
public:
	Transformation();
	void setPosition(float x, float y, float z);
	void setRotation(float angleX, glm::vec3 axis);
	void setScale(float s);

	glm::mat4 getMatrix() const;
};