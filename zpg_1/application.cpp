#include "application.h"
#include <iostream>
#include "tree.h"
#include "sphere.h"
#include "suzi_flat.h"
#include "suzi_smooth.h"
#include "bushes.h"
#include "ground.h"
#include "triangle.h"
#include "plain.h"
#include "lambertShader.h"
#include "constantShader.h"
#include "phongShader.h"
#include "blinnPhongShader.h"


void Application::error_callback(int error, const char* description) {
	fputs(description, stderr);
}
void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS)
	{
		Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

		std::cout << "Key pressed: " << key << " (numeric keys: 1=49, 2=50, 3=51)" << std::endl;

		// Handle numeric keys (both numpad and regular)
		if (key == GLFW_KEY_1 || key == GLFW_KEY_KP_1) {
			std::cout << "Switching to Scene 1 (Constant)" << std::endl;
			app->switchToScene(0);
		}
		else if (key == GLFW_KEY_2 || key == GLFW_KEY_KP_2) {
			std::cout << "Switching to Scene 2 (Lambert)" << std::endl;
			app->switchToScene(1);
		}
		else if (key == GLFW_KEY_3 || key == GLFW_KEY_KP_3) {
			std::cout << "Switching to Scene 3 (Phong)" << std::endl;
			app->switchToScene(2);
		}
		else if (key == GLFW_KEY_4 || key == GLFW_KEY_KP_4) {  
			std::cout << "Switching to Scene 4 (PhongBlinn)" << std::endl;
			app->switchToScene(3);
		}
		else if (key == GLFW_KEY_5 || key == GLFW_KEY_KP_5) {
			std::cout << "Switching to Scene 5 (trees)" << std::endl;
			app->switchToScene(4);
		}
		else if (key == GLFW_KEY_ESCAPE)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		else {
			std::cout << "Unknown key - try keys 1, 2, or 3" << std::endl;
		}
	}
}
void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Application::window_focus_callback(GLFWwindow* window, int focused) {
	printf("window_focus_callback \n"); 
}

void Application::window_iconify_callback(GLFWwindow* window, int iconified) {
	printf("window_iconify_callback \n"); 
}

void Application::cursor_callback(GLFWwindow* window, double x, double y) {
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	if(app->rightMouseButtonPressed) {
		double xOffset = x - app->lastMouseX;
		double yOffset = app->lastMouseY - y; 

		Camera* camera = nullptr;
		if (app->currentSceneIndex < app->scenes.size()) {
			camera = app->scenes[app->currentSceneIndex]->getCamera();
		}
		if (camera) {
			camera->processMouseMovement(static_cast<float>(xOffset), static_cast<float>(yOffset));
		}
	}

	app->lastMouseX = x;
	app->lastMouseY = y;
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS) {
			app->rightMouseButtonPressed = true;
			glfwGetCursorPos(window, &app->lastMouseX, &app->lastMouseY);
		}
		else if (action == GLFW_RELEASE) {
			app->rightMouseButtonPressed = false;
		}
	}
	if(action == GLFW_PRESS)
	{
		printf("Mouse button pressed: %d\n", button);
	}
}

void Application::processInput()
{
	if (!window) return;

	Camera* camera = nullptr;
	if (currentSceneIndex < scenes.size()) {
		camera = scenes[currentSceneIndex]->getCamera();
	}

	if (!camera) return;

	//wasd 
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->moveForward();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->moveBackward();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->moveLeft();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->moveRight();

	//sipky
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera->moveUp();
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera->moveDown();

}

void Application::switchToScene(int index)
{
	if (index >= 0 && index < scenes.size())
	{
		currentSceneIndex = index;
		std::cout << "Switched to scene: " << scenes[index]->getName() << std::endl;
		std::cout << "Current scene index: " << currentSceneIndex << std::endl;
	}
	else {
		std::cerr << "Invalid scene index: " << index << std::endl;
	}
}

void Application::generateForest(Scene* scene, int treeCount, int bushCount)
{
	std::cout << "Generating forest with " << treeCount << " trees and " << bushCount << " bushes..." << std::endl;

	for(int i = 0; i < treeCount; ++i)
	{
		auto treeObj = std::make_unique<DrawableObject>(new Model(tree, sizeof(tree) / sizeof(tree[0])));

		float x = (rand() % 90 - 45) * 0.1f; // Random x between -1.0 and 1.0
		float z = (rand() % 90 - 45) * 0.1f; // Random z between -1.0 and 1.0

		float scale = 0.1f + (rand() % 16) * 0.01f;
		float rotation = rand() % 360;

		treeObj->getTransformation().setPosition(x, -1.0f, z);
		treeObj->getTransformation().setScale(scale);
		treeObj->getTransformation().setRotation(rotation, glm::vec3(0, 1, 0));
		treeObj->setShaderManager(std::make_unique<LambertShader>());

		scene->addObject(std::move(treeObj));
	}

	for (int i = 0; i < bushCount; i++) {
		auto bushObj = std::make_unique<DrawableObject>(new Model(bushes, 8730));

		// Náhodná pozice (trochu jiná distribuce než stromy)
		float x = (rand() % 90 - 45) * 0.1f;
		float z = (rand() % 90 - 45) * 0.1f;

		// Keøe jsou menší než stromy
		float scale = 0.1f + (rand() % 11) * 0.005f; // 0.02f to 0.05f
		float rotation = rand() % 360;

		bushObj->getTransformation().setPosition(x, -1.0f, z); // Trochu výše než stromy
		bushObj->getTransformation().setScale(scale);
		bushObj->getTransformation().setRotation(rotation, glm::vec3(0, 1, 0));
		bushObj->setShaderManager(std::make_unique<LambertShader>());

		scene->addObject(std::move(bushObj));
	}

	std::cout << "Forest generation complete!" << std::endl;
}

void Application::createScenes()
{
	auto scene1 = std::make_unique<Scene>("Triangle Scene");


	auto triangleObj = std::make_unique<DrawableObject>(new Triangle());
	triangleObj->getTransformation().setPosition(0.0f, 0.0f, 0.0f);
	triangleObj->setShaderManager(std::make_unique<PhongShader>());
	scene1->addObject(std::move(triangleObj));

	auto light1 = std::make_unique<Light>(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
	scene1->setLight(std::move(light1));

	scenes.push_back(std::move(scene1));

	auto scene2 = std::make_unique<Scene>("Spheres Scene");


	auto sphereObj1 = std::make_unique<DrawableObject>(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])));
	sphereObj1->getTransformation().setPosition(-1.0f, 1.0f, -3.0f);
	sphereObj1->getTransformation().setScale(0.5f);
	sphereObj1->setShaderManager(std::make_unique<PhongShader>());
	scene2->addObject(std::move(sphereObj1));

	auto sphereObj2 = std::make_unique<DrawableObject>(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])));
	sphereObj2->getTransformation().setPosition(1.0f, 1.0f, -3.0f);
	sphereObj2->getTransformation().setScale(0.5f);
	sphereObj2->setShaderManager(std::make_unique<PhongShader>());
	scene2->addObject(std::move(sphereObj2));

	auto sphereObj3 = std::make_unique<DrawableObject>(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])));
	sphereObj3->getTransformation().setPosition(-1.0f, -1.0f, -3.0f);
	sphereObj3->getTransformation().setScale(0.5f);
	sphereObj3->setShaderManager(std::make_unique<PhongShader>());
	scene2->addObject(std::move(sphereObj3));

	auto sphereObj4 = std::make_unique<DrawableObject>(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])));
	sphereObj4->getTransformation().setPosition(1.0f, -1.0f, -3.0f);
	sphereObj4->getTransformation().setScale(0.5f);
	sphereObj4->setShaderManager(std::make_unique<PhongShader>());
	scene2->addObject(std::move(sphereObj4));

	auto light2 = std::make_unique<Light>(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.5f);
	scene2->setLight(std::move(light2));

	scenes.push_back(std::move(scene2));


	auto forestScene = std::make_unique<Scene>("Forest Scene");


	auto groundObj = std::make_unique<DrawableObject>(new Model(plain, sizeof(plain) / sizeof(plain[0])));
	groundObj->getTransformation().setPosition(0.0f, -1.0f, 0.0f);
	groundObj->getTransformation().setScale(5.0f); // zvìtšení plochy
	groundObj->setShaderManager(std::make_unique<ConstantShader>(glm::vec3(0.07f, 0.31f, 0.09f)));
	forestScene->addObject(std::move(groundObj));

	generateForest(forestScene.get(), 50, 50); // 50 stromù, 50 keøù
	
	auto light3 = std::make_unique<Light>(glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
	forestScene->setLight(std::move(light3));
	
	scenes.push_back(std::move(forestScene));


	auto scene4 = std::make_unique<Scene>("Solar System");

	// Slunce
	auto sunObj = std::make_unique<DrawableObject>(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])));
	sunObj->getTransformation().setPosition(0.0f, 0.0f, 0.0f);
	sunObj->getTransformation().setScale(1.0f);
	sunObj->setShaderManager(std::make_unique<ConstantShader>(glm::vec3(1.0f, 0.9f, 0.1f)));
	scene4->addObject(std::move(sunObj));

	// Zemì
	auto earthObj = std::make_unique<DrawableObject>(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])));
	auto earthComposite = earthObj->createCompositeTransformation();

	//kolem slunce
	auto earthOrbit = earthComposite->createAndAddTransformation();\

	//vzdalenost od zeme
	auto earthDistance = earthComposite->createAndAddTransformation();
	earthDistance->setPosition(3.0f, 0.0f, 0.0f);

	//kolem sebe
	auto earthTransform = earthComposite->createAndAddTransformation();
	earthTransform->setScale(0.4f);

	earthObj->setShaderManager(std::make_unique<PhongShader>());

	earthObj->onUpdate = [earthOrbit](float deltaTime) {
		static float earthAngle = 0.0f;
		earthAngle += 2.0f * deltaTime; // 30 degrees per second
		if (earthAngle > 360.0f) earthAngle -= 360.0f;

		earthOrbit->setRotation(earthAngle, glm::vec3(0, 1, 0));
	};
	scene4->addObject(std::move(earthObj));


	auto moonObj = std::make_unique<DrawableObject>(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])));
	auto moonComposite = moonObj->createCompositeTransformation();
	//spolu s zemi
	auto moonSunOrbit = moonComposite->createAndAddTransformation();

	auto moonBasePosition = moonComposite->createAndAddTransformation();
	moonBasePosition->setPosition(3.0f, 0.0f, 0.0f);

	//kolem zeme
	auto moonOrbit = moonComposite->createAndAddTransformation();

	//vzdalenost od zeme
	auto moonDistance = moonComposite->createAndAddTransformation();
	moonDistance->setPosition(0.8f, 0.0f, 0.0f);

	//kolem sebe
	auto moonTransform = moonComposite->createAndAddTransformation();
	moonTransform->setScale(0.2f);

	moonObj->setShaderManager(std::make_unique<PhongShader>());

	moonObj->onUpdate = [moonSunOrbit,moonOrbit](float deltaTime) {
		static float earthAngle = 0.0f;
		static float moonAngle = 0.0f;
		earthAngle += 2.0f * deltaTime; // 30 degrees per second
		moonAngle += 8.0f * deltaTime; // 60 degrees per second
		if (earthAngle > 360.0f) earthAngle -= 360.0f;
		if (moonAngle > 360.0f) moonAngle -= 360.0f;


		moonSunOrbit->setRotation(earthAngle, glm::vec3(0, 1, 0));
		moonOrbit->setRotation(moonAngle, glm::vec3(0, 1, 0));
	};
	scene4->addObject(std::move(moonObj));

	auto light4 = std::make_unique<Light>(
		glm::vec3(0.0f, 0.0f, 0.0f),  // pozice - stejná jako Slunce
		glm::vec3(1.0f, 0.9f, 0.7f),  // barva svìtla - teplá žlutá (jako sluneèní svìtlo)
		2.0f                           // intenzita - vyšší pro lepší osvìtlení
	);
	scene4->setLight(std::move(light4));

	scenes.push_back(std::move(scene4));

}

Application::Application(int width, int height, const char* title) : 
	width(width), 
	height(height), 
	title(title), 
	window(nullptr), 
	currentSceneIndex(0), 
	rightMouseButtonPressed(false), 
	lastMouseX(0.0), 
	lastMouseY(0.0)
{
}

Application::~Application()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Application::initialize()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);
	glfwSetWindowUserPointer(window, this);

	rightMouseButtonPressed = false;
	lastMouseX = width / 2.0;
	lastMouseY = height / 2.0;

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "ERROR: could not initialize GLEW\n";
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);

	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);

	createScenes();
	
	for (auto& scene:scenes) {

		auto camera = std::make_unique<Camera>();
		scene->setCamera(std::move(camera));

		std::cout << "Initialized scene: " << scene->getName() << std::endl;
	}

	std::cout << "Application initialized with " << scenes.size() << " scenes" << std::endl;
	std::cout << "Controls: 1-" << scenes.size() << " - switch scenes "<< std::endl;
	std::cout << "Mouse: Right button + move - look around" << std::endl;
}

void Application::run()
{
	double lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		float deltaTime = static_cast<float>(currentTime - lastTime);
		lastTime = currentTime;

		processInput();

		if (currentSceneIndex < scenes.size()) {
			scenes[currentSceneIndex]->update(deltaTime);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Vykreslení aktuální scény
		if (currentSceneIndex < scenes.size()) {
			scenes[currentSceneIndex]->draw(width,height);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}