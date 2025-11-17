#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "shaderProgram.h"

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
	struct MaterialData {
		glm::vec3 Ka = glm::vec3(0.1f); // ambient
		glm::vec3 Kd = glm::vec3(0.8f); // diffuse
		glm::vec3 Ks = glm::vec3(0.0f); // specular
		float Ns = 32.0f;              // shininess
		GLuint diffuseTexID = 0;   // texture OpenGL ID
		bool hasTexture = false;
		std::string diffuseTexName; // for debug/log
	};
	std::vector<MaterialData> materials;

	Model();
	Model(const float* vertices, GLsizei Count);
	Model(const char* objFileName);
	virtual ~Model();
	virtual void draw() const;

	void applyMaterialToShader(ShaderProgram* shader) const;
};