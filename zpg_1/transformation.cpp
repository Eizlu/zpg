#include  "transformation.h"

Transformation::Transformation()
	: position(0.0f),
	  rotation(0.0f),
	  scale(1.0f)
{
}

void Transformation::setPosition(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
}

void Transformation::setRotation(float angleX, glm::vec3 axis)
{
	rotation = axis * angleX;
}

void Transformation::setRotation(float angleX, float angleY, float angleZ)
{
	rotation = glm::vec3(angleX, angleY, angleZ);
}

void Transformation::setScale(float sx, float sy, float sz)
{
	scale = glm::vec3(sx, sy, sz);
}

void Transformation::setScale(float s)
{
	scale = glm::vec3(s);
}

glm::mat4 Transformation::getMatrix() const
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, position);

	model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
	model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
	model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));

	model = glm::scale(model, scale);

	return model;
}