#include "scene.h"
#include <iostream>
#include "shaderLoader.h"
#include "spotLight.h"

Scene::Scene(const std::string& sceneName) : name(sceneName), camera(nullptr)
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

void Scene::update(float deltaTime)
{
	for (auto& obj : objects) {
		obj->update(deltaTime);
	}

	if (camera) {
		for (auto& light : lights) {
			SpotLight* spot = dynamic_cast<SpotLight*>(light.get());
			if (spot && spot->isEnabled()) {
				// pozice = pozice kamery
				spot->setPosition(camera->getPosition());
				// smìr = kamera front
				spot->setDirection(camera->getFront());
			}
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
	if (camera) {
		for (auto& obj : objects) {
			if (auto shader = obj->getShaderProgram()) {
				camera->addObserver(shader); 
			}
		}
		camera->notifyObservers();  
	}
}

void Scene::addLight(std::unique_ptr<Light> light)
{
	if (light) {
		for (auto& obj : objects) {
			if (auto shader = obj->getShaderProgram()) {
				light->addObserver(shader); 
			}
		}
		lights.push_back(std::move(light));
		lights.back()->notifyObservers(); 
	}
}

void Scene::setLight(std::unique_ptr<Light> lgt)
{
	addLight(std::move(lgt));
}


void Scene::draw( int windowWidth, int windowHeight)
{
	if (objects.empty()) return;
	if (!camera) return;


	for (auto& obj : objects) {
		auto shader = obj->getShaderProgram();
		if (!shader) continue;

		shader->use();
		
		if (camera)
		{
			shader->setViewMatrix(camera->LookAt(camera->getPosition(), camera->getPosition() + camera->getFront(), camera->getUp()));
			shader->setProjectionMatrix(camera->getProjectionMatrix());
			shader->setViewPosition(camera->getPosition());
		}

		for (int i = 0; i < lights.size(); ++i)
		{
			lights[i]->applyToShader(*shader, i);
		}
		shader->setUniform("numLights", static_cast<int>(lights.size()));

		obj->draw();
		glUseProgram(0);
	}
}