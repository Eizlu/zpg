#include "rotationAroundPoint.h"

RotationAroundPoint::RotationAroundPoint(const glm::vec3& point, float angle, const glm::vec3& axis)
	: point(point), angle(angle), axis(axis)
{
}

void RotationAroundPoint::setPoint(const glm::vec3& newPoint)
{
	point = newPoint;
}

void RotationAroundPoint::setAngle(float newAngle)
{
	angle = newAngle;
}

void RotationAroundPoint::setAxis(const glm::vec3& newAxis)
{
	axis = glm::normalize(newAxis);
}

glm::mat4 RotationAroundPoint::getMatrix() const
{
	glm::mat4 translationToOrigin = glm::translate(glm::mat4(1.0f), -point);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);
	glm::mat4 translationBack = glm::translate(glm::mat4(1.0f), point);
	return translationBack * rotationMatrix * translationToOrigin;
}

std::unique_ptr<Transformation> RotationAroundPoint::clone() const
{
	return std::make_unique<RotationAroundPoint>(*this);
}