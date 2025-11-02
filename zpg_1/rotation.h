#pragma once
#include "transformation.h"
#include <memory>

class Rotation : public Transformation
{
private:
	float angle;
	glm::vec3 axis;
public:
	Rotation(float angle, const glm::vec3& axis);

	void setAngle(float angle);
	void setAxis(const glm::vec3& axis);

	float getAngle() const;
	const glm::vec3& getAxis() const;

	glm::mat4 getMatrix() const;

	std::unique_ptr<Transformation> clone() const;
};