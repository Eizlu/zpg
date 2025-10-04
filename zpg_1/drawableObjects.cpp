#include "drawableObject.h"

DrawableObject::DrawableObject(Model* model)
	: model(model)
{
}

DrawableObject::~DrawableObject()
{
	delete model;
}

void DrawableObject::draw(ShaderProgram& shader)
{
	shader.setUniformMat4("model", transformation.getMatrix());
	model->draw();
}