#pragma once
#include "transformation.h"
#include <memory>

class RotationAroundPoint : public Transformation
{
private:
	glm::vec3 point;
	float angle;
	glm::vec3 axis;
public:
	RotationAroundPoint(const glm::vec3& point, float angle, const glm::vec3& axis);

	void setPoint(const glm::vec3& point);
	void setAngle(float angle);
	void setAxis(const glm::vec3& axis);

	glm::mat4 getMatrix() const;

	std::unique_ptr<Transformation> clone() const;
};