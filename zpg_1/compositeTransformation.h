#pragma once
#include "transformation.h"
#include <vector>
#include <memory>

class CompositeTransformation
{
private:
	std::vector<std::shared_ptr<Transformation>> transformations;
public:
	CompositeTransformation();
	CompositeTransformation(const CompositeTransformation& other);

	void addTranslation(float x, float y, float z);
	void addScale(float sx, float sy, float sz);
	void addScale(float uniformScale);
	void addRotation(float angle, const glm::vec3& axis);
	void addRotationEuler(float angleX, float angleY, float angleZ);
	void addRotationAroundPoint(const glm::vec3& point, float angle, const glm::vec3& axis);

	void addTransformation(const std::shared_ptr<Transformation>& transformation);

	glm::mat4 getMatrix() const;
	size_t getTransformationCount() const;
	Transformation* getTransformation(size_t index) const;

	template<typename T>
	T* getTransformationAs(size_t index) const
	{
		if (index >= transformations.size())
		{
			return nullptr;
		}
		return dynamic_cast<T*>(transformations[index].get());
	}
};