#pragma once
#include "model.h"
#include "transformation.h"
#include "shaderProgram.h"
#include "compositeTransformation.h"

class DrawableObject
{
protected:
	Model* model;
	Transformation transformation;
	std::shared_ptr<CompositeTransformation> compositeTransformation;
public:
	DrawableObject( Model* model);
	virtual ~DrawableObject();
	virtual void draw(ShaderProgram& shader);

	Transformation& getTransformation() { return transformation; }

	std::shared_ptr<CompositeTransformation> createCompositeTransformation();
	void setCompositeTransformation(std::shared_ptr<CompositeTransformation> composite);
	bool hasCompositeTransformation() const { return compositeTransformation != nullptr; }
};