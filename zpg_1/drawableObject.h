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
	std::shared_ptr<CompositeTransformation> compositeTransformation;
	std::unique_ptr<ShaderManager> shaderManager;
	std::unique_ptr<ShaderProgram> shaderProgram;
public:
	DrawableObject( Model* model);
	virtual ~DrawableObject();

	virtual void draw();
	virtual void update( float deltaTime);


	void translate(float x, float y, float z);
	void scale(float sx, float sy, float sz);
	void scale(float uniformScale);
	void rotate(float angle, const glm::vec3& axis);
	void rotateEuler(float angleX, float angleY, float angleZ);
	void rotateAroundPoint(const glm::vec3& point, float angle, const glm::vec3& axis);


	std::shared_ptr<CompositeTransformation> getCompositeTransformation();
	std::shared_ptr<CompositeTransformation> createCompositeTransformation();

	void setCompositeTransformation(std::shared_ptr<CompositeTransformation> composite);
	bool hasCompositeTransformation() const;
	
	ShaderProgram* getShaderProgram() { return shaderProgram.get(); }

	void applyPhongShader(); 
	void applyBlinnPhongShader();
	void applyLambertShader();
	void applyConstantShader(const glm::vec3& color);

	std::function<void(float)> onUpdate = [](float deltaTime) {};
};