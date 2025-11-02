#pragma once
#include "transformation.h"
#include <memory>

class RotationEuler : public Transformation
{
private:
	glm::vec3 rotation;
public:
	RotationEuler(float angleX, float angleY, float angleZ);
	RotationEuler(const glm::vec3& vec);

	void setRotation(float angleX, float angleY, float angleZ);
	void setRotation(const glm::vec3& vec);
	const glm::vec3& getRotation() const;

	glm::mat4 getMatrix() const;
	std::unique_ptr<Transformation> clone() const;
};