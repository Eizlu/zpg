#include "drawableObject.h"

DrawableObject::DrawableObject(Model* model)
	: model(model), compositeTransformation(nullptr)
{
}

DrawableObject::~DrawableObject()
{
	delete model;
}

std::shared_ptr<CompositeTransformation> DrawableObject::createCompositeTransformation()
{
	compositeTransformation = std::make_shared<CompositeTransformation>();
	return compositeTransformation;
}

void DrawableObject::setCompositeTransformation(std::shared_ptr<CompositeTransformation> composite)
{
	compositeTransformation = composite;
}

void DrawableObject::draw(ShaderProgram& shader)
{
	if (compositeTransformation)
	{
		shader.setUniform("model", compositeTransformation->getMatrix());
	}
	else
	{
		shader.setUniform("model", transformation.getMatrix());
	}
	model->draw();
}