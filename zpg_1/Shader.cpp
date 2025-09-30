/**
 * @file shader.cpp
 *
 * @brief shader definition
 *
 * @author Èeslárová Eliška CES0022
  **/

#include <iostream>
#include "Shader.h"

GLuint Shader::compileShader(const char* source, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "Shader compilation error: " << infoLog << std::endl;
	}
	return shader;
}

Shader::Shader(const char* vertexSource, const char* fragmentSource) {
	GLuint vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	GLint success;
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(programID, 512, nullptr, infoLog);
		std::cerr << "Shader compilation error: " << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(programID);
}

void Shader::use() const {
	glUseProgram(programID);
}