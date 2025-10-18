#include "scene.h"
#include <iostream>

Scene::Scene(const std::string& sceneName): shaderProgram(nullptr), name(sceneName)
{
}


Scene::~Scene()
{
	cleanup();
}

void Scene::cleanup()
{
	for (auto& obj : objects) {
		delete obj;
	}
	objects.clear();
}

void Scene::addObject(DrawableObject* object)
{
	objects.push_back(object);
}

void Scene::setCamera(Camera* cam)
{
	camera = cam;
}


void Scene::init()
{

	const char* vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;" //vertex position
		"layout(location=1) in vec3 normal;"	//vertex color
		"out vec3 vertexNormal;" //output to fragment shader
		"uniform mat4 model;" //model matrix
		"uniform mat4 view;" //pohled
		"uniform mat4 projection;"
		"void main () {"
		"	gl_Position = projection * view * model * vec4(vp, 1.0);"
		"   vertexNormal = normalize(normal);"
		"}";



	const char* fragment_shader =
		"#version 330\n"
		"in vec3 vertexNormal;" //input from vertex shader
		"out vec4 fragColor;"	//output  fragment color
		"void main () {"
		"	fragColor=vec4(vertexNormal * 0.5 + 0.5, 1.0); "
		"}";


	shaderProgram = std::make_unique<ShaderProgram>(vertex_shader, fragment_shader);

	std::cout << "Scene '" << name << "' initialized with " << objects.size() << " objects" << std::endl;
}

void Scene::draw()
{
	shaderProgram->use();

	if (camera)
	{
		// nastavuju do shaderu
		glm::mat4 view = camera->LookAt(camera->getPosition(), camera->getPosition() + camera->getFront(), camera->getUp());

		//dynamicke prepocitani podle resize okna
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f);

		shaderProgram->setUniform("view", view);
		shaderProgram->setUniform("projection", projection); 

	}

	for ( auto& obj : objects) {
		shaderProgram->setUniform("model", obj->getTransformation().getMatrix());
		obj->draw(*shaderProgram);
	}
}