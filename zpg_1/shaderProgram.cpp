#include "shaderProgram.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>


ShaderProgram::ShaderProgram(const char* vertexSource, const char* fragmentSource)
{
	Shader vertex(GL_VERTEX_SHADER, vertexSource);
	Shader fragment(GL_FRAGMENT_SHADER, fragmentSource);

	programID = glCreateProgram();
	glAttachShader(programID, vertex.shaderID);
	glAttachShader(programID, fragment.shaderID);
	glLinkProgram(programID);

	GLint success;
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetProgramInfoLog(programID, 512, nullptr, infoLog);
		std::cerr << "Program linking error: " << infoLog << std::endl;
	}
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(programID);
}

void ShaderProgram::use() const
{
	glUseProgram(programID);
}

void ShaderProgram::setUniformMat4(const std::string& name, const glm::mat4& mat) const
{
	GLint location = glGetUniformLocation(programID, name.c_str());
	if (location != -1) {
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}
}
