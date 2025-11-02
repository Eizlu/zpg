#include "rotation.h"

Rotation::Rotation(float angle, const glm::vec3& axis) : angle(angle), axis(axis)
{
}

void Rotation::setAngle(float newAngle)
{
	angle = newAngle;
}

void Rotation::setAxis(const glm::vec3& newAxis)
{
	axis = glm::normalize(newAxis);
}

float Rotation::getAngle() const
{
	return angle;
}

const glm::vec3& Rotation::getAxis() const
{
	return axis;
}

glm::mat4 Rotation::getMatrix() const
{
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);
	return rotationMatrix;
}

std::unique_ptr<Transformation> Rotation::clone() const
{
	return std::make_unique<Rotation>(*this);
}