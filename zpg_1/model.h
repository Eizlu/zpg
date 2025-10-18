#pragma once
#include <GL/glew.h>

//muze byt treba shapetype nabidka

class Model
{
protected:
	GLuint VBO, VAO;
	GLsizei vertexCount;
	const float* externalVertices;
	GLsizei externalVertexCount;
	bool useExternalData;
public:
	Model();
	Model(const float* vertices, GLsizei Count);
	virtual ~Model();
	virtual void draw() const;
};