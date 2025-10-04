#pragma once
#include "model.h"
#include "transformation.h"
#include "shaderProgram.h"

class DrawableObject
{
protected:
	Model* model;
	Transformation transformation;
public:
	DrawableObject( Model* model);
	virtual ~DrawableObject();
	virtual void draw(ShaderProgram& shader);
	Transformation& getTransformation() { return transformation; }
};