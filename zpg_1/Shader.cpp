/**
 * @file shader.cpp
 *
 * @brief shader definition
 *
 * @author Èeslárová Eliška CES0022
  **/

#include <iostream>
#include "shader.h"


Shader::Shader(GLenum type, const char* source) {
	shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &source, NULL);
	glCompileShader(shaderID);

	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
		std::cerr << "Shader compilation error: " << infoLog << std::endl;
	}
}

Shader::~Shader() {
	glDeleteShader(shaderID);
}
