/**
 * @file shape.h
 *
 * @brief shape declaration
 *
 * @author Èeslárová Eliška CES0022
  **/

#pragma once
#include <GL/glew.h>
#include <glm/ext/vector_float3.hpp>

struct Vertex {
	float position[4]; // x, y, z, w
	float color[4];    // r, g, b, a
};

class Shader;

class Shape {
protected:
	GLuint VBO, VAO;
	const Vertex* vertices;
	size_t vertexCount;
	glm::vec3 position;
public:
	Shape(const Vertex* verts, size_t count);
	virtual ~Shape();

	void setPosition(float x, float y, float z);
	void draw(const Shader& shader) const;

};