#include "shaderProgram.h"
#include "camera.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>


ShaderProgram::ShaderProgram(const char* vertexSource, const char* fragmentSource) : windowWidth(1200), windowHeight(800)
{
	Shader vertex(GL_VERTEX_SHADER, vertexSource);
	Shader fragment(GL_FRAGMENT_SHADER, fragmentSource);

	programID = glCreateProgram();
	glAttachShader(programID, vertex.shaderID);
	glAttachShader(programID, fragment.shaderID);
	glLinkProgram(programID);

	glDetachShader(programID, vertex.shaderID);
	glDetachShader(programID, fragment.shaderID);

	GLint success;
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetProgramInfoLog(programID, 512, nullptr, infoLog);
		std::cerr << "Program linking error: " << infoLog << std::endl;
	}
}

ShaderProgram::~ShaderProgram()
{
	if (programID)
	{
		glDeleteProgram(programID);
	}
}

void ShaderProgram::use() const
{
	glUseProgram(programID);
}

void ShaderProgram::setWindowSize(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
}

//matice
void ShaderProgram::setUniform(const std::string& name, const glm::mat4& value) const
{
	GLint location = glGetUniformLocation(programID, name.c_str());
	if (location != -1) {
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
	else {
		std::cerr << "Warning: Uniform '" << name << "' not found in shader program." << std::endl;
	}
}

//vektor
void ShaderProgram::setUniform(const std::string& name, const glm::vec3& value) const
{
	GLint location = glGetUniformLocation(programID, name.c_str());
	if (location != -1) {
		glUniform3f(location, value.x, value.y, value.z);
	}
}

//float
void ShaderProgram::setUniform(const std::string& name, float value) const
{
	GLint location = glGetUniformLocation(programID, name.c_str());
	if (location != -1) {
		glUniform1f(location, value);
	}
}

//integer
void ShaderProgram::setUniform(const std::string& name, int value) const
{
	GLint location = glGetUniformLocation(programID, name.c_str());
	if (location != -1) {
		glUniform1i(location, value);
	}
}

//boolean
void ShaderProgram::setUniform(const std::string& name, bool value) const
{
	GLint location = glGetUniformLocation(programID, name.c_str());
	if (location != -1) {
		glUniform1i(location, value ? 1 : 0);
	}
}

void ShaderProgram::onCameraChanged(const Camera& camera)
{
	use();

	glm::mat4 view = camera.LookAt(camera.getPosition(),
		camera.getPosition() + camera.getFront(),
		camera.getUp());

	float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

	setUniform("view", view);
	setUniform("projection", projection);

	std::cout << "Camera updated in shader - Position: ("
		<< camera.getPosition().x << ", "
		<< camera.getPosition().y << ", "
		<< camera.getPosition().z << ")" << std::endl;
}