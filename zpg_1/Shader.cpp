/**
 * @file shader.cpp
 *
 * @brief shader definition
 *
 * @author Èeslárová Eliška CES0022
  **/

#include <iostream>
#include "shader.h"

//GLuint Shader::compileShader(const char* source, GLenum shaderType) {
//	GLuint shader = glCreateShader(shaderType);
//	glShaderSource(shader, 1, &source, NULL);
//	glCompileShader(shader);
//
//	GLint success;
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		GLchar infoLog[512];
//		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
//		std::cerr << "Shader compilation error: " << infoLog << std::endl;
//	}
//	return shader;
//}

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
