#include "scene.h"
#include "triangle.h"
#include "square.h"

Scene::Scene()
{
	shaderProgram = nullptr;

}


void Scene::init()
{

	const char* vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec4 vp;" //vertex position
		"layout(location=1) in vec4 color;"	//vertex color
		"out vec4 vertexColor;" //output to fragment shader
		"uniform mat4 model;" //model matrix
		"void main () {"
		"	gl_Position = model * vp;"
		"	vertexColor = color;"
		"}";



	const char* fragment_shader =
		"#version 330\n"
		"in vec4 vertexColor;" //input from vertex shader
		"out vec4 fragColor;"	//output  fragment color
		"void main () {"
		"	fragColor=vertexColor; "
		"}";

	Shader vertexShader(GL_VERTEX_SHADER, vertex_shader);
	Shader fragmentShader(GL_FRAGMENT_SHADER, fragment_shader);

	shaderProgram = std::make_unique<ShaderProgram>(vertex_shader, fragment_shader);
	// pøidání objektù do scény
	auto triangle = new DrawableObject(new Triangle());
	triangle->getTransformation().setPosition(-0.5f, 0.0f, 0.0f);
	objects.push_back(triangle);

	auto square = new DrawableObject(new Square());
	square->getTransformation().setPosition(0.5f, 0.0f, 0.0f);
	objects.push_back(square);
}

void Scene::draw()
{
	shaderProgram->use();
	for ( auto& obj : objects) {
		obj->draw(*shaderProgram);
	}
}