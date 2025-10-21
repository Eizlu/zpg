#include "drawableObject.h"

DrawableObject::DrawableObject(Model* model)
	: model(model), compositeTransformation(nullptr)
{
}

DrawableObject::~DrawableObject()
{
	delete model;
}

void DrawableObject::update(float deltaTime)
{
	onUpdate(deltaTime);
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

void DrawableObject::setShaderManager(std::unique_ptr<ShaderManager> manager)
{
	shaderManager = std::move(manager);
	applyShaderManager();
}

void DrawableObject::applyShaderManager()
{
	if (shaderManager)
	{
		shaderProgram = std::make_unique<ShaderProgram>(
			shaderManager->getVertexShader().c_str(),
			shaderManager->getFragmentShader().c_str()
		);
		shaderManager->setupUniforms(*shaderProgram);
	}
}

void DrawableObject::draw()
{
	if (!shaderProgram) {
		// Fallback - použít nìjaký defaultní shader
		return;
	}

	shaderProgram->use();

	if (compositeTransformation)
	{
		shaderProgram->setUniform("model", compositeTransformation->getMatrix());
	}
	else
	{
		shaderProgram->setUniform("model", transformation.getMatrix());
	}
	model->draw();
}