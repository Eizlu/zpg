#pragma once
#include <GL/glew.h>
#include <string>
#include "shader.h"
#include <glm/glm.hpp>


class ShaderProgram
{
private:
	GLuint programID;
public:
	ShaderProgram(const char* vertexSource, const char* fragmentSource);
	~ShaderProgram();
	void use() const;
	void setUniformMat4(const std::string& name, const glm::mat4& mat) const;
};