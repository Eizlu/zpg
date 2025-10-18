#pragma once
#include <vector>
#include "shaderProgram.h"
#include "drawableObject.h"
#include <memory>
#include "camera.h"

class Scene {
private:
	std::unique_ptr<ShaderProgram> shaderProgram;
	std::vector<std::unique_ptr<DrawableObject>> objects;
	std::string name;
	std::unique_ptr<Camera> camera;
public:	
	Scene(const std::string& sceneName = "Unnamed Scene");
	~Scene();
	void init();
	void draw( int windowWidth , int windowHeight);
	void cleanup();

	void addObject(std::unique_ptr<DrawableObject> object);
	void setCamera(std::unique_ptr<Camera> cam);
	Camera* getCamera() { return camera.get(); }

	const std::string& getName() const { return name; }
};

