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
	GLuint shaderID;
	friend class ShaderProgram;
public:
	Shader(GLenum type, const char* source);
	~Shader();

};

//class Shader {
//private:
//	GLuint programID;
//
//	float r,g,b;
//public:
//	Shader(float red, float green, float blue);
//	~Shader();
//
//	void create()
//	void use();
//};