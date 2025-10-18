#include "compositeTransformation.h"

CompositeTransformation::CompositeTransformation()
{

}

void CompositeTransformation::addTransformation(const std::shared_ptr<Transformation>& transformation) {
	transformations.push_back(transformation);
}

std::shared_ptr<Transformation> CompositeTransformation::createAndAddTransformation() {
	auto transformation = std::make_shared<Transformation>();
	transformations.push_back(transformation);
	return transformation;
}


glm::mat4 CompositeTransformation::getMatrix() const {
	glm::mat4 compositeMatrix(1.0f);

	for (const auto& transformation : transformations) {
		compositeMatrix = compositeMatrix * transformation->getMatrix();
	}
	return compositeMatrix;
}

size_t CompositeTransformation::getTransformationCount() const {
	return transformations.size();
}

std::shared_ptr<Transformation> CompositeTransformation::getTransformation(size_t index) const {
	if (index < transformations.size()) {
		return transformations[index];
	}
	return nullptr;
}