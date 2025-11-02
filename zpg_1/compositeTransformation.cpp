#include "compositeTransformation.h"
#include "translation.h"
#include "scale.h"
#include "rotation.h"
#include "rotationEuler.h"
#include "rotationAroundPoint.h"

CompositeTransformation::CompositeTransformation()
{
}

CompositeTransformation::CompositeTransformation(const CompositeTransformation& other)
{
	for (const auto& transformation : other.transformations)
	{
		transformations.push_back(std::shared_ptr<Transformation>(transformation->clone()));
	}
}

void CompositeTransformation::addTranslation(float x, float y, float z)
{
	transformations.push_back(std::make_shared<Translation>(x, y, z));
}

void CompositeTransformation::addScale(float sx, float sy, float sz)
{
	transformations.push_back(std::make_shared<Scale>(sx, sy, sz));
}

void CompositeTransformation::addScale(float uniformScale)
{
	transformations.push_back(std::make_shared<Scale>(uniformScale));
}

void CompositeTransformation::addRotation(float angle, const glm::vec3& axis)
{
	transformations.push_back(std::make_shared<Rotation>(angle, axis));
}

void CompositeTransformation::addRotationEuler(float angleX, float angleY, float angleZ)
{
	transformations.push_back(std::make_shared<RotationEuler>(angleX, angleY, angleZ));
}

void CompositeTransformation::addRotationAroundPoint(const glm::vec3& point, float angle, const glm::vec3& axis)
{
	transformations.push_back(std::make_shared<RotationAroundPoint>(point, angle, axis));
}

void CompositeTransformation::addTransformation(const std::shared_ptr<Transformation>& transformation)
{
	transformations.push_back(transformation);
}

glm::mat4 CompositeTransformation::getMatrix() const
{
	glm::mat4 result(1.0f);
	for (const auto& transformation : transformations)
	{
		result = result * transformation->getMatrix();
	}
	return result;
}

size_t CompositeTransformation::getTransformationCount() const
{
	return transformations.size();
}

Transformation* CompositeTransformation::getTransformation(size_t index) const
{
	if (index < transformations.size()) {
		return transformations[index].get();
	}
	return nullptr;
}