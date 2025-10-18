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

	void addTransformation(const std::shared_ptr<Transformation>& transformation);
	std::shared_ptr<Transformation> createAndAddTransformation();
	glm::mat4 getMatrix() const;
	size_t getTransformationCount() const;
	std::shared_ptr<Transformation> getTransformation(size_t index) const;
};