#pragma once
#include <vector>
#include "shaderProgram.h"
#include "drawableObject.h"
#include <memory>

class Scene {
private:
	std::unique_ptr<ShaderProgram> shaderProgram;
	std::vector<DrawableObject*> objects;
public:	
	Scene();
	~Scene() = default;
	void init();
	void draw();
};