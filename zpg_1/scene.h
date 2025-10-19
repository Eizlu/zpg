#pragma once
#include <vector>
#include "shaderProgram.h"
#include "drawableObject.h"
#include <memory>
#include "camera.h"
#include "light.h"
#include "shaderManager.h"

class Scene {
private:
	std::unique_ptr<ShaderProgram> shaderProgram;
	std::unique_ptr<ShaderManager> shaderManager;
	std::vector<std::unique_ptr<DrawableObject>> objects;
	std::string name;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Light> light;
public:	
	Scene(const std::string& sceneName = "Unnamed Scene");
	~Scene();
	void init();
	void draw( int windowWidth , int windowHeight);
	void cleanup();

	void setShaderManager(std::unique_ptr<ShaderManager> manager);
	void applyShaderManager();

	void addObject(std::unique_ptr<DrawableObject> object);
	
	Camera* getCamera() { return camera.get(); }
	void setCamera(std::unique_ptr<Camera> cam);

	Light* getLight() { return light.get(); }
	void setLight(std::unique_ptr<Light> lgt);

	const std::string& getName() const { return name; }

};

