#pragma once
#include "transformation.h"

class CustomTransformation : public Transformation
{
public:
	glm::mat4 getMatrix() const override
	{
		glm::mat4 m(1.0f);
		m[3][3] = 20.0f;  // zmìna homogenní složky
		return m;
	}
	std::unique_ptr<Transformation> clone() const override
	{
		return std::make_unique<CustomTransformation>(*this);
	}
};