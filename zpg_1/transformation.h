#pragma once
#include <GL/glew.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

class Transformation
{
public:
	//Transformation() = default;
	virtual glm::mat4 getMatrix() const=0;
	virtual std::unique_ptr<Transformation> clone() const = 0;
	virtual ~Transformation() = default;

};