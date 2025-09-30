/**
 * @file shape.cpp
 *
 * @brief shape definition
 *
 * @author Èeslárová Eliška CES0022
  **/

#include "Shape.h"
#include "Shader.h"
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Shape::Shape(const Vertex* verts, size_t count)
	: vertices(verts), vertexCount(count)
{
	// Create and bind the Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// Create and bind the Vertex Buffer Object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	// Define the vertex position attribute
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	// Define the vertex color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*4));
	glEnableVertexAttribArray(1);
	// Unbind the VAO (it's a good practice to unbind any buffer/array to prevent strange bugs)
	glBindVertexArray(0);
}

Shape::~Shape()
{
	// Clean up VBO and VAO
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}


void Shape::setPosition(float x, float y, float z) {
	position = glm::vec3(x, y, z);
}

void Shape::draw(const Shader& shader) const
{
	shader.use();
	glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
	GLuint modelLoc = glGetUniformLocation(shader.getID(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(0);
}