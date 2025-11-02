#pragma once
#include "transformation.h"
#include <memory>

class Translation: public Transformation
{
private: 
	glm::vec3 translation;
public:
	Translation(float x, float y, float z);
	Translation(const glm::vec3& vec);

	void setTranslation(float x, float y, float z);
	void setTranslation(const glm::vec3& vec);
	const glm::vec3& getTranslation() const;

	glm::mat4 getMatrix() const ;
	std::unique_ptr<Transformation> clone() const;

};