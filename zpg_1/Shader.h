/**
 * @file shader.h
 *
 * @brief shader declaration
 *
 * @author Èeslárová Eliška CES0022
  **/
#pragma once
#include <GL/glew.h>
#include <string>

class Shader {
private:
	GLuint programID;

	GLuint compileShader(const char* source, GLenum shaderType);
public:
	Shader(const char* vertexSource, const char* fragmentSource);
	~Shader();

	void use() const;
	GLuint getID() const { return programID; }
};