#include "scene.h"
#include <iostream>
#include "lambertShader.h"
#include "constantShader.h"
#include "phongShader.h"
#include "blinnPhongShader.h"

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

void Scene::setShaderManager(std::unique_ptr<ShaderManager> manager)
{
	shaderManager = std::move(manager);
	applyShaderManager();
}

void Scene::applyShaderManager()
{
	if (shaderManager)
	{
		shaderProgram = std::make_unique<ShaderProgram>(
			shaderManager->getVertexShader().c_str(),
			shaderManager->getFragmentShader().c_str()
		);
		shaderManager->setupUniforms(*shaderProgram);

		if (camera)
		{
			camera->addObserver(shaderProgram.get());
			camera->notifyObservers();
		}
		if (light)
		{
			light->addObserver(shaderProgram.get());
			light->notifyObservers();
		}
	}
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

void Scene::setLight(std::unique_ptr<Light> lgt)
{
	light = std::move(lgt);
	if (light && shaderProgram)
	{
		light->addObserver(shaderProgram.get());
		light->notifyObservers();
	}
}


void Scene::init()
{

	if(shaderManager)
	{
		applyShaderManager();
	}
	else {
		const char* vertex_shader =
			"#version 330\n"
			"layout(location=0) in vec3 vp;" //vertex position
			"layout(location=1) in vec3 vn;"	//vertex normal
			"uniform mat4 model;" //model matrix
			"uniform mat4 view;" //pohled
			"uniform mat4 projection;"
			"out vec3 worldPos;"
			"out vec3 worldNorm;" //output to fragment shader
			"void main () {"
			"   worldPos = vec3(model * vec4(vp, 1.0));"
			"   worldNorm = mat3(transpose(inverse(model))) * vn;"
			"	gl_Position = projection * view * model * vec4(vp, 1.0);"
			"}";



		const char* fragment_shader =
			"#version 330\n"
			"in vec3 worldNorm;" //input from vertex shader
			"in vec3 worldPos;" //input from vertex shader
			"out vec4 fragColor;"	//output  fragment color
			"void main () {"
			"   fragColor = vec4(worldNorm * 0.5 + 0.5, 1.0);"
			"}";


		shaderProgram = std::make_unique<ShaderProgram>(vertex_shader, fragment_shader);

		if (camera)
		{
			camera->addObserver(shaderProgram.get());
		}
		if (light)
		{
			light->addObserver(shaderProgram.get());
		}
	}

	std::cout << "Scene '" << name << "' initialized with " << objects.size() << " objects" << std::endl;
}

void Scene::draw( int windowWidth, int windowHeight)
{

	if (!shaderProgram) {
		std::cerr << "ERROR: Shader program is null in scene: " << name << std::endl;
		return;
	}

	// Zkontroluj jestli máme objekty k renderování
	if (objects.empty()) {
		std::cout << "No objects to render in scene: " << name << std::endl;
		return;
	}

	shaderProgram->setWindowSize(windowWidth, windowHeight);
	shaderProgram->use();
	for ( auto& obj : objects) {
		shaderProgram->setUniform("model", obj->getTransformation().getMatrix());
		obj->draw(*shaderProgram);
	}
}