#include "drawableObject.h"
#include "shaderLoader.h"

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

void DrawableObject::translate(float x, float y, float z)
{
	if (!compositeTransformation)
		createCompositeTransformation();
	compositeTransformation->addTranslation(x, y, z);
}

void DrawableObject::scale(float sx, float sy, float sz)
{
	if (!compositeTransformation)
		createCompositeTransformation();
	compositeTransformation->addScale(sx, sy, sz);
}

void DrawableObject::scale(float uniformScale)
{
	if (!compositeTransformation)
		createCompositeTransformation();
	compositeTransformation->addScale(uniformScale);
}

void DrawableObject::rotate(float angle, const glm::vec3& axis)
{
	if (!compositeTransformation)
		createCompositeTransformation();
	compositeTransformation->addRotation(angle, axis);
}

void DrawableObject::rotateEuler(float angleX, float angleY, float angleZ)
{
	if (!compositeTransformation)
		createCompositeTransformation();
	compositeTransformation->addRotationEuler(angleX, angleY, angleZ);
}

void DrawableObject::rotateAroundPoint(const glm::vec3& point, float angle, const glm::vec3& axis)
{
	if (!compositeTransformation)
		createCompositeTransformation();
	compositeTransformation->addRotationAroundPoint(point, angle, axis);
}

std::shared_ptr<CompositeTransformation> DrawableObject::getCompositeTransformation()
{
	return compositeTransformation;
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

bool DrawableObject::hasCompositeTransformation() const
{
	return compositeTransformation != nullptr;
}

//pøidaná úprava hodnoty uniform "w"
void DrawableObject::draw()
{
	if (!shaderProgram || !compositeTransformation)
		return;

	shaderProgram->use();

	shaderProgram->setUniform("w", 1.0f);

	shaderProgram->setUniform("model", compositeTransformation->getMatrix());

	model->applyMaterialToShader(shaderProgram.get());

	if (shaderManager)
		shaderManager->setupUniforms(*shaderProgram);

	model->draw();

	glUseProgram(0);
}

//V 3D grafice se pro transformace objektù používají 4x4 matice. Abychom mohli jednoduše kombinovat tranclace, rotace a škálování, používáme homogenní
// souøadnice (x,y,z,w), kde w je obvykle 1 pro body v prostoru. Po transformaci pøi perspektivní projekci se x, y, z vydìlí w, aby se získaly 
// zpìt kartézské souøadnice. Tzn. Když se zvýší w, objekt vypadá menší, protože jeho x,y,z se zmenší po vydìlení vìtším w.
//
// V mé aplikaci jsem testovala rùzné kodnoty w, i vlastní matici s w=20, a objekty se škálují oèekávanì a perspektivní efekt funguje správnì.

void DrawableObject::applyPhongShader()
{
	std::string vertex = loadShaderFromFile("shaders/phong.vert");
	std::string fragment = loadShaderFromFile("shaders/phong.frag");

	shaderProgram = std::make_unique<ShaderProgram>(vertex.c_str(), fragment.c_str());

}

void DrawableObject::applyBlinnPhongShader()
{
	std::string vertex = loadShaderFromFile("shaders/blinnPhong.vert");
	std::string fragment = loadShaderFromFile("shaders/blinnPhong.frag");

	shaderProgram = std::make_unique<ShaderProgram>(vertex.c_str(), fragment.c_str());
}

void DrawableObject::applyLambertShader()
{
	std::string vertex = loadShaderFromFile("shaders/lambert.vert");
	std::string fragment = loadShaderFromFile("shaders/lambert.frag");

	shaderProgram = std::make_unique<ShaderProgram>(vertex.c_str(), fragment.c_str());
}

void DrawableObject::applyConstantShader(const glm::vec3& color)
{
	std::string vertex = loadShaderFromFile("shaders/constant.vert");
	std::string fragment = loadShaderFromFile("shaders/constant.frag");

	shaderProgram = std::make_unique<ShaderProgram>(vertex.c_str(), fragment.c_str());

	// Pokud shader potøebuje uniform "objectColor" (nebo jak jsi ho nazvala):
	shaderProgram->use();
	shaderProgram->setUniform("objectColor", color);
}
