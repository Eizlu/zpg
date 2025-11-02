#include "rotationEuler.h"

RotationEuler::RotationEuler(float angleX, float angleY, float angleZ) : rotation(angleX, angleY, angleZ)
{
}

RotationEuler::RotationEuler(const glm::vec3& vec) : rotation(vec)
{
}

void RotationEuler::setRotation(float angleX, float angleY, float angleZ)
{
	rotation = glm::vec3(angleX, angleY, angleZ);
}

void RotationEuler::setRotation(const glm::vec3& vec)
{
	rotation = vec;
}

const glm::vec3& RotationEuler::getRotation() const
{
	return rotation;
}

glm::mat4 RotationEuler::getMatrix() const
{
	glm::mat4 rotationMatrix(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, rotation.x, glm::vec3(1, 0, 0));
	rotationMatrix = glm::rotate(rotationMatrix, rotation.y, glm::vec3(0, 1, 0));
	rotationMatrix = glm::rotate(rotationMatrix, rotation.z, glm::vec3(0, 0, 1));
	return rotationMatrix;
}

std::unique_ptr<Transformation> RotationEuler::clone() const
{
	return std::make_unique<RotationEuler>(*this);
}