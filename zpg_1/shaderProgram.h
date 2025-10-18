#pragma once
#include <GL/glew.h>
#include <string>
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "cameraObserver.h"


class ShaderProgram:public CameraObserver
{
private:
	GLuint programID;
	int windowWidth;
	int windowHeight;
public:
	ShaderProgram(const char* vertexSource, const char* fragmentSource);
	~ShaderProgram();
	void use() const;

	void setUniform(const std::string& name, const glm::mat4& value) const;
	void setUniform(const std::string& name, const glm::vec3& value) const;
	void setUniform(const std::string& name, float value) const;
	void setUniform(const std::string& name, int value) const;
	void setUniform(const std::string& name, bool value) const;

	void setWindowSize(int width, int height);

	void onCameraChanged(const Camera& camera) override;
};