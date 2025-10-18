#include "model.h"
#include <GL/glew.h>

Model::Model() : VBO(0), VAO(0), vertexCount(0), useExternalData(false), externalVertices(nullptr), externalVertexCount(0)
{
}

Model::Model(const float* vertices, GLsizei Count) : VBO(0), VAO(0), vertexCount(0), useExternalData(true), externalVertices(vertices), externalVertexCount(Count)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, externalVertexCount * sizeof(float), externalVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	vertexCount = externalVertexCount / 6; // Assuming each vertex has 6 components (3 for position, 3 for color)
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