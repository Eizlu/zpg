#include "model.h"
#include <GL/glew.h>

Model::Model() : VBO(0), VAO(0), vertexCount(0)
{
}

Model::~Model()
{
	if (VBO) glDeleteBuffers(1, &VBO);
	if (VAO) glDeleteVertexArrays(1, &VAO);
}

void Model::draw() const
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);
}