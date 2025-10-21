#pragma once
#include "model.h"
#include "transformation.h"
#include "shaderProgram.h"
#include "compositeTransformation.h"
#include "shaderManager.h"
#include <functional>

class DrawableObject
{
protected:
	Model* model;
	Transformation transformation;
	std::shared_ptr<CompositeTransformation> compositeTransformation;
	std::unique_ptr<ShaderManager> shaderManager;
	std::unique_ptr<ShaderProgram> shaderProgram;
public:
	DrawableObject( Model* model);
	virtual ~DrawableObject();
	virtual void draw();
	virtual void update( float deltaTime);


	Transformation& getTransformation() { return transformation; }

	std::shared_ptr<CompositeTransformation> createCompositeTransformation();
	void setCompositeTransformation(std::shared_ptr<CompositeTransformation> composite);
	bool hasCompositeTransformation() const { return compositeTransformation != nullptr; }
	
	void setShaderManager(std::unique_ptr<ShaderManager> manager);
	void applyShaderManager();

	ShaderProgram* getShaderProgram() { return shaderProgram.get(); }

	std::function<void(float)> onUpdate = [](float deltaTime) {};
};