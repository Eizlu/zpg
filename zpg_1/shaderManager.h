#pragma once
#include <string>
#include "shaderProgram.h"

class ShaderManager
{
public:
	virtual ~ShaderManager() = default;
	virtual std::string getVertexShader() const = 0;
	virtual std::string getFragmentShader() const = 0;
	virtual void setupUniforms(class ShaderProgram& shaderProgram) const = 0;
};