#pragma once
#include <vector>
#include "shaderProgram.h"
#include "drawableObject.h"
#include <memory>
#include "camera.h"
#include "light.h"

class Scene {
private:
	std::vector<std::unique_ptr<DrawableObject>> objects;
	std::string name;
	std::unique_ptr<Camera> camera;
	std::vector<std::unique_ptr<Light>> lights;
public:	
	Scene(const std::string& sceneName = "Unnamed Scene");
	~Scene();
	//void init();
	void draw( int windowWidth , int windowHeight);
	void cleanup();
	void update(float deltaTime);

	void addObject(std::unique_ptr<DrawableObject> object);
	void addLight(std::unique_ptr<Light> light);
	
	Camera* getCamera() { return camera.get(); }
	void setCamera(std::unique_ptr<Camera> cam);

	Light* getLight() const { return lights.empty() ? nullptr : lights[0].get(); }
	void setLight(std::unique_ptr<Light> lgt);

	const std::string& getName() const { return name; }
	const std::vector<std::unique_ptr<Light>>& getLights() const { return lights; }

};

