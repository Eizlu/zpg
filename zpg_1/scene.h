#pragma once
#include <vector>
#include "shaderProgram.h"
#include "drawableObject.h"
#include <memory>
#include "camera.h"

class Scene {
private:
	std::unique_ptr<ShaderProgram> shaderProgram;
	std::vector<DrawableObject*> objects;
	std::string name;
	Camera* camera;
public:	
	Scene(const std::string& sceneName = "Unnamed Scene");
	~Scene();
	void init();
	void draw();
	void cleanup();

	void addObject(DrawableObject* object);
	void setCamera(Camera * cam);
	Camera* getCamera() const { return camera; }

	const std::string& getName() const { return name; }
};

