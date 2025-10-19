#pragma once
#include "shaderManager.h"
#include <glm/ext/vector_float3.hpp>

class ConstantShader : public ShaderManager
{
private:
	glm::vec3 color;
public:
	ConstantShader(const glm::vec3& color = glm::vec3(1.0f)) : color(color) {}

	std::string getVertexShader() const override
	{
		return
			"#version 330\n"
			"layout(location=0) in vec3 vp;" //vertex position
			"layout(location=1) in vec3 vn;"	//vertex normal
			"uniform mat4 model;" //model matrix
			"uniform mat4 view;" //pohled
			"uniform mat4 projection;"
			"out vec3 worldPos;"
			"out vec3 worldNorm;" //output to fragment shader
			"void main () {"
			"   worldPos = vec3(model * vec4(vp, 1.0));"
			"   worldNorm = mat3(transpose(inverse(model))) * vn;"
			"	gl_Position = projection * view * model * vec4(vp, 1.0);"
			"}";
	}
	std::string getFragmentShader() const override
	{
		return
			"#version 330\n"
			"in vec3 worldNorm;" //input from vertex shader
			"in vec3 worldPos;" //input from vertex shader
			"out vec4 fragColor;"	//output  fragment color
			"uniform vec3 objectColor;"
			"void main () {"
			"	fragColor=vec4(objectColor, 1.0); "
			"}";
	}

	void setupUniforms(class ShaderProgram& shaderProgram) const override
	{
		shaderProgram.setUniform("objectColor", color);
	}

};