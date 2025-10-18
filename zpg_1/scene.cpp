#include "scene.h"
#include <iostream>

Scene::Scene(const std::string& sceneName) : shaderProgram(nullptr), name(sceneName), camera(nullptr)
{
}


Scene::~Scene()
{
	cleanup();
}

void Scene::cleanup()
{
	objects.clear();
}

void Scene::addObject(std::unique_ptr<DrawableObject> object)
{
	objects.push_back(std::move(object));
}

void Scene::setCamera(std::unique_ptr<Camera> cam)
{
	camera = std::move(cam);
	if(camera && shaderProgram)
	{
		camera->addObserver(shaderProgram.get());
		camera->notifyObservers();
	}
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

	if (camera)
	{
		camera->addObserver(shaderProgram.get());
	}

	std::cout << "Scene '" << name << "' initialized with " << objects.size() << " objects" << std::endl;
}

void Scene::draw( int windowWidth, int windowHeight)
{
	shaderProgram->setWindowSize(windowWidth, windowHeight);
	shaderProgram->use();
	for ( auto& obj : objects) {
		shaderProgram->setUniform("model", obj->getTransformation().getMatrix());
		obj->draw(*shaderProgram);
	}
}