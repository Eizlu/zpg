#pragma once
#include "shaderManager.h"
#include <glm/ext/vector_float3.hpp>

class LambertShader : public ShaderManager
{
public:
	std::string getVertexShader() const override
	{
		return
			"#version 400\n"
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
			"#version 400\n"
			"in vec3 worldNorm;" //input from vertex shader
			"in vec3 worldPos;" //input from vertex shader
			"out vec4 fragColor;"	//output  fragment color
			"void main () {"
			"	vec3 lightPosition = vec3 (10.0 ,10.0 ,10.0);"
			"	vec3 lightDir = lightPosition - worldPos;"
			"	float diff = max(dot(normalize(lightDir), normalize(worldNorm)), 0.0); "
			"	vec4 ambient = vec4 (0.1 ,0.1 ,0.1 ,1.0);"
			" 	vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);"
			"	fragColor = ambient + ( diff * objectColor ); "
			"}";
	}

	void setupUniforms(class ShaderProgram& shaderProgram) const override
	{
		// No additional uniforms to set for this simple Lambert shader
	}

};