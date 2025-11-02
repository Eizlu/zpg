#pragma once
#include <GL/glew.h>
#include <string>
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "observer.h"


class ShaderProgram : public Observer
{
private:
	GLuint programID;
	//int windowWidth;
	//int windowHeight;
public:
	ShaderProgram(const char* vertexSource, const char* fragmentSource);
	~ShaderProgram();
	void use() const;

	void setUniform(const std::string& name, const glm::mat4& value) const;
	void setUniform(const std::string& name, const glm::vec3& value) const;
	void setUniform(const std::string& name, float value) const;
	void setUniform(const std::string& name, int value) const;
	void setUniform(const std::string& name, bool value) const;

	//void setWindowSize(int width, int height);
	void onSubjectChanged() override;


	void setViewMatrix(const glm::mat4& view);
	void setProjectionMatrix(const glm::mat4& proj);
	void setViewPosition(const glm::vec3& pos);
	void setLightData(int index, const glm::vec3& pos,
		const glm::vec3& color, float intensity, float attenuation);
};