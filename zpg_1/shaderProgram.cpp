#include "shaderProgram.h"
#include "camera.h"
#include "light.h" 
#include <iostream>
#include <glm/gtc/type_ptr.hpp>


ShaderProgram::ShaderProgram(const char* vertexSource, const char* fragmentSource) 
{

	std::cout << "Compiling vertex shader..." << std::endl;
	Shader vertex(GL_VERTEX_SHADER, vertexSource);
	std::cout << "Compiling fragment shader..." << std::endl;
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
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "Shader program linked successfully! ID: " << programID << std::endl;
	}

	use();
	GLint modelLoc = glGetUniformLocation(programID, "model");
	GLint viewLoc = glGetUniformLocation(programID, "view");
	GLint projLoc = glGetUniformLocation(programID, "projection");
	std::cout << "Uniform locations - model: " << modelLoc << ", view: " << viewLoc << ", projection: " << projLoc << std::endl;
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

// Helper to bind this program if not already bound, optionally restore previous
static inline GLint bindProgramIfNeeded(GLuint programID) {
	GLint prev = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &prev);
	if ((GLuint)prev != programID) {
		glUseProgram(programID);
	}
	return prev;
}
static inline void restoreProgramIfNeeded(GLint prev, GLuint programID) {
	if ((GLuint)prev != programID) {
		glUseProgram(prev);
	}
}

//matice
void ShaderProgram::setUniform(const std::string& name, const glm::mat4& value) const
{
	GLint prev = bindProgramIfNeeded(programID);

	GLint location = glGetUniformLocation(programID, name.c_str());
	if (location != -1) {
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
	else {
		std::cerr << "Warning: Uniform '" << name << "' not found in shader program." << std::endl;
	}
	restoreProgramIfNeeded(prev, programID);
}

//vektor
void ShaderProgram::setUniform(const std::string& name, const glm::vec3& value) const
{
	GLint prev = bindProgramIfNeeded(programID);

	GLint location = glGetUniformLocation(programID, name.c_str());
	if (location != -1) {
		glUniform3f(location, value.x, value.y, value.z);
	}

	restoreProgramIfNeeded(prev, programID);
}

//float
void ShaderProgram::setUniform(const std::string& name, float value) const
{
	GLint prev = bindProgramIfNeeded(programID);

	GLint location = glGetUniformLocation(programID, name.c_str());
	if (location != -1) {
		glUniform1f(location, value);
	}

	restoreProgramIfNeeded(prev, programID);
}

//integer
void ShaderProgram::setUniform(const std::string& name, int value) const
{
	GLint prev = bindProgramIfNeeded(programID);

	GLint location = glGetUniformLocation(programID, name.c_str());
	if (location != -1) {
		glUniform1i(location, value);
	}

	restoreProgramIfNeeded(prev, programID);
}

//boolean
void ShaderProgram::setUniform(const std::string& name, bool value) const
{
	GLint prev = bindProgramIfNeeded(programID);

	GLint location = glGetUniformLocation(programID, name.c_str());
	if (location != -1) {
		glUniform1i(location, value ? 1 : 0);
	}

	restoreProgramIfNeeded(prev, programID);
}
void ShaderProgram::onSubjectChanged() {
}


void ShaderProgram::setViewMatrix(const glm::mat4& view) { setUniform("view", view); }
void ShaderProgram::setProjectionMatrix(const glm::mat4& proj) { setUniform("projection", proj); }
void ShaderProgram::setViewPosition(const glm::vec3& pos) { setUniform("viewPos", pos); }

void ShaderProgram::setLightData(int index, const glm::vec3& pos,
	const glm::vec3& color, float intensity, float attenuation)
{
	setUniform("lights[" + std::to_string(index) + "].position", pos);
	setUniform("lights[" + std::to_string(index) + "].color", color);
	setUniform("lights[" + std::to_string(index) + "].intensity", intensity);
	setUniform("lights[" + std::to_string(index) + "].attenuation", attenuation);
}