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

	void setUniform(const std::string& name, const glm::mat4& value) const;
	void setUniform(const std::string& name, const glm::vec3& value) const;
	void setUniform(const std::string& name, float value) const;
	void setUniform(const std::string& name, int value) const;
	void setUniform(const std::string& name, bool value) const;
};