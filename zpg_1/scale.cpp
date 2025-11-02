#include "scale.h"

Scale::Scale(float sx, float sy, float sz) : scale(sx, sy, sz)
{
}

Scale::Scale(float uniformScale) : scale(uniformScale)
{
}

Scale::Scale(const glm::vec3& vec) : scale(vec)
{
}

void Scale::setScale(float sx, float sy, float sz)
{
	scale = glm::vec3(sx, sy, sz);
}

void Scale::setScale(float uniformScale)
{
	scale = glm::vec3(uniformScale);
}

const glm::vec3& Scale::getScale() const
{
	return scale;
}

glm::mat4 Scale::getMatrix() const
{
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
	return scaleMatrix;
}

std::unique_ptr<Transformation> Scale::clone() const
{
	return std::make_unique<Scale>(*this);
}