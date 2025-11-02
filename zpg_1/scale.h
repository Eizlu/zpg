#pragma once
#include "transformation.h"
#include <memory>

class Scale : public Transformation
{
private:
	glm::vec3 scale;
public:
	Scale(float sx, float sy, float sz);
	Scale(float uniformScale);
	Scale(const glm::vec3& vec);

	void setScale(float sx, float sy, float sz);
	void setScale(float uniformScale);
	const glm::vec3& getScale() const;

	glm::mat4 getMatrix() const ;

	std::unique_ptr<Transformation> clone() const ;


};