#pragma once
#include <GL/glew.h>

//muze byt treba shapetype nabidka

class Model
{
protected:
	GLuint VBO, VAO;
	GLsizei vertexCount;
public:
	Model();
	virtual ~Model();
	virtual void draw() const;
};