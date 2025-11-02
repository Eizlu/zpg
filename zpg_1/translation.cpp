#include "translation.h"

Translation::Translation(float x, float y, float z) : translation(x, y, z)
{
}

Translation::Translation(const glm::vec3& vec) : translation(vec)
{
}

void Translation::setTranslation(float x, float y, float z)
{
	translation = glm::vec3(x, y, z);
}

void Translation::setTranslation(const glm::vec3& vec)
{
	translation = vec;
}

const glm::vec3& Translation::getTranslation() const
{
	return translation;
}

glm::mat4 Translation::getMatrix() const
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);
	return translationMatrix;
}

std::unique_ptr<Transformation> Translation::clone() const
{
	return std::make_unique<Translation>(*this);
}