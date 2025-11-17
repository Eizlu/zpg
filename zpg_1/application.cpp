#include "application.h"
#include <iostream>
#include "models/models.h"
#include "shaderLoader.h"
#include "rotation.h"
#include "pointLight.h"
#include "ambientLight.h"


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
		else if (key == GLFW_KEY_F) {
			Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

			for (auto& light : app->scenes[app->currentSceneIndex]->getLights()) {
				SpotLight* spot = dynamic_cast<SpotLight*>(light.get());
				if (spot) {
					bool newState = !spot->isEnabled();
					spot->setEnabled(newState);
					std::cout << (newState ? "Flashlight ON" : "Flashlight OFF") << std::endl;
				}
			}
		}
		else {
			std::cout << "Unknown key - try keys 1, 2, or 3" << std::endl;
		}
	}
}
void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app) {
		for (auto& scene : app->scenes) {
			if (auto camera = scene->getCamera()) {
				camera->updateAspectRatio(width, height);
			}
		}
	}
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
		auto treeModel = new Model(tree, sizeof(tree) / sizeof(tree[0]));
		auto treeObj = std::make_unique<DrawableObject>(treeModel);

		float x = (rand() % 90 - 45) * 0.1f; // Random x between -1.0 and 1.0
		float z = (rand() % 90 - 45) * 0.1f; // Random z between -1.0 and 1.0

		float scale = 0.1f + (rand() % 16) * 0.01f;
		float rotation = rand() % 360;

		auto composite = treeObj->createCompositeTransformation();
		composite->addTranslation(x, -1.0f, z);
		composite->addScale(scale);
		composite->addRotation(rotation, glm::vec3(0, 1, 0));

		treeObj->applyPhongShader();
		scene->addObject(std::move(treeObj));
	}

	for (int i = 0; i < bushCount; i++) {
		auto bushModel = new Model(bushes, 8730);
		auto bushObj = std::make_unique<DrawableObject>(bushModel);

		// Náhodná pozice (trochu jiná distribuce než stromy)
		float x = (rand() % 90 - 45) * 0.1f;
		float z = (rand() % 90 - 45) * 0.1f;

		// Keøe jsou menší než stromy
		float scale = 0.1f + (rand() % 11) * 0.1f; // 0.02f to 0.05f
		float rotation = rand() % 360;

		auto composite = bushObj->createCompositeTransformation();
		composite->addTranslation(x, -1.0f, z);
		composite->addScale(scale);
		composite->addRotation(rotation, glm::vec3(0, 1, 0));

		bushObj->applyPhongShader();
		scene->addObject(std::move(bushObj));
	}

	std::cout << "Forest generation complete!" << std::endl;
}

void Application::createFireFlies(Scene* scene, int fireFlyCount)
{
	struct FireflyData {
		float time;
		float speed;
		float amplitudeX, amplitudeY, amplitudeZ;
		float freqX, freqY, freqZ;
		float phaseX, phaseY, phaseZ;
	};

	for (int i = 0; i < fireFlyCount; i++)
	{
		float x = (rand() % 80 - 40) * 0.1f;
		float y = (rand() % 10) * 0.1f;
		float z = (rand() % 80 - 40) * 0.1f;

		glm::vec3 fireflyColor(1.0f, 0.9f, 0.2f);

		auto fireflyLight = std::make_unique<PointLight>(glm::vec3(x, y, z), fireflyColor, 0.8f, 5.0f);
		PointLight* lightPtr = fireflyLight.get(); 
		scene->addLight(std::move(fireflyLight));

		auto fireflyObj = std::make_unique<DrawableObject>(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])));
		auto composite = fireflyObj->createCompositeTransformation();
		composite->addTranslation(x, y, z);
		composite->addScale(0.01f);
		
		fireflyObj->applyConstantShader(glm::vec3(1.0f, 0.9f, 0.1f));

		FireflyData data;
		data.time = (rand() % 100) * 0.1f;
		data.speed =0.1+(rand() % 3) * 0.01f;
		data.amplitudeX = (rand() % 20) * 0.1f;
		data.amplitudeY = (rand() % 10) * 0.1f;
		data.amplitudeZ = (rand() % 20) * 0.1f;
		data.freqX = 0.2f + (rand() % 10) * 0.05f;
		data.freqY = 0.3f + (rand() % 10) * 0.05f;
		data.freqZ = 0.2f + (rand() % 10) * 0.05f;
		data.phaseX = (rand() % 100) * 0.01f;
		data.phaseY = (rand() % 100) * 0.01f;
		data.phaseZ = (rand() % 100) * 0.01f;

		glm::vec3 startPosition(x, y, z);

		DrawableObject* objPtr = fireflyObj.get();

		fireflyObj->onUpdate = [lightPtr, objPtr, startPosition, data](float deltaTime) mutable {
			data.time += deltaTime * data.speed;

			float newX = startPosition.x + sin(data.time * data.freqX + data.phaseX) * data.amplitudeX;
			float newZ = startPosition.z + cos(data.time * data.freqZ + data.phaseZ) * data.amplitudeZ;
			float newY = startPosition.y + sin(data.time * data.freqY + data.phaseY) * data.amplitudeY;

			lightPtr->setPosition(glm::vec3(newX, newY, newZ));

			auto newComposite = std::make_shared<CompositeTransformation>();
			newComposite->addTranslation(newX, newY, newZ);
			newComposite->addScale(0.01f);

			objPtr->setCompositeTransformation(newComposite);
		};

		scene->addObject(std::move(fireflyObj));
	}
}

void Application::createScenes()
{
	auto scene1 = std::make_unique<Scene>("Shrek Scene");

	auto shrekModel = new Model("shrek/shrek.obj");
	auto shrekObj = std::make_unique<DrawableObject>(shrekModel);
	shrekObj->translate(0.0f, -0.5f, 0.0f);
	shrekObj->scale(0.5);
	shrekObj->applyPhongShader();
	scene1->addObject(std::move(shrekObj));

	auto ambient1 = std::make_unique<AmbientLight>(glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);
	scene1->setLight(std::move(ambient1));

	auto point1 = std::make_unique<PointLight>(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f), 3.0f, 1.0f);
	scene1->setLight(std::move(point1));

	scenes.push_back(std::move(scene1));



	auto scene2 = std::make_unique<Scene>("Spheres Scene");

	auto sphereObj1 = std::make_unique<DrawableObject>(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])));
	sphereObj1->translate(-1.0f, 0.0f, 0.0f);
	sphereObj1->scale(0.5f);
	sphereObj1->applyPhongShader();
	scene2->addObject(std::move(sphereObj1));

	auto sphereObj2 = std::make_unique<DrawableObject>(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])));
	sphereObj2->translate(0.0f, 1.0f, 0.0f);
	sphereObj2->scale(0.5f);
	sphereObj2->applyPhongShader();
	scene2->addObject(std::move(sphereObj2));

	auto sphereObj3 = std::make_unique<DrawableObject>(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])));
	sphereObj3->translate(1.0f, 0.0f, 0.0f);
	sphereObj3->scale(0.5f);
	sphereObj3->applyPhongShader();
	scene2->addObject(std::move(sphereObj3));

	auto sphereObj4 = std::make_unique<DrawableObject>(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])));
	sphereObj4->translate(0.0f, -1.0f, 0.0f);
	sphereObj4->scale(0.5f);
	sphereObj4->applyPhongShader();
	scene2->addObject(std::move(sphereObj4));

	auto point2 = std::make_unique<PointLight>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 2.0f, 1.0f);
	scene2->setLight(std::move(point2));

	scenes.push_back(std::move(scene2));



	auto forestScene = std::make_unique<Scene>("Forest Scene");


	auto groundObj = std::make_unique<DrawableObject>(new Model(plain, sizeof(plain) / sizeof(plain[0])));
	groundObj->translate(0.0f, -1.0f, 0.0f);
	groundObj->scale(5.0f); // zvìtšení plochy
	groundObj->applyConstantShader(glm::vec3(0.0157f, 0.149f, 0.051f));
	forestScene->addObject(std::move(groundObj));

	generateForest(forestScene.get(), 50, 50); // 50 stromù, 50 keøù
	
	auto moonLight = std::make_unique<PointLight>(
		glm::vec3(0.0f, 10.0f, 5.0f),
		glm::vec3(0.7f, 0.7f, 1.0f),  
		0.1f,                         
		0.1f                          
	);
	forestScene->setLight(std::move(moonLight));

	createFireFlies(forestScene.get(), 6);

	auto flashlight = std::make_unique<SpotLight>(
		glm::vec3(0.0f, 0.0f, 0.0f),   // pozice se bude aktualizovat podle kamery
		glm::vec3(0.0f, 0.0f, -1.0f),  // smìr se bude aktualizovat podle kamery
		glm::vec3(1.0f, 1.0f, 0.9f),   // barva svìtla
		1.5f,                           // intenzita
		0.05f,                          // attenuation
		10.0f                           // cutoff (v°)
	);
	flashlight->setEnabled(false);  // zaèíná vypnutá
	forestScene->addLight(std::move(flashlight));
	
	scenes.push_back(std::move(forestScene));


	auto scene4 = std::make_unique<Scene>("Solar System");

	// Slunce
	auto sunObj = std::make_unique<DrawableObject>(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])));
	sunObj->translate(0.0f, 0.0f, 0.0f);
	sunObj->scale(1.0f);
	sunObj->applyConstantShader(glm::vec3(1.0f, 0.9f, 0.1f));
	scene4->addObject(std::move(sunObj));

	// Zemì
	auto earthObj = std::make_unique<DrawableObject>(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])));
	auto earthComposite = earthObj->createCompositeTransformation();

	//kolem slunce
	auto earthOrbit = std::make_shared<Rotation>(0.0f, glm::vec3(0, 1, 0));
	earthComposite->addTransformation(earthOrbit);
	earthComposite->addTranslation(3.0f, 0.0f, 0.0f);
	earthComposite->addRotation(0.0f, glm::vec3(0, 1, 0));
	earthComposite->addScale(0.4f);

	earthObj->applyPhongShader();

	earthObj->onUpdate = [earthOrbit](float deltaTime) {
		static float earthAngle = 0.0f;
		earthAngle += 1.0f * deltaTime; // 30 degrees per second
		if (earthAngle > 360.0f) earthAngle -= 360.0f;
		earthOrbit->setAngle(earthAngle);
	};
	scene4->addObject(std::move(earthObj));


	auto moonObj = std::make_unique<DrawableObject>(new Model(sphere, sizeof(sphere) / sizeof(sphere[0])));
	auto moonComposite = moonObj->createCompositeTransformation();

	auto moonEarthOrbit = std::make_shared<Rotation>(0.0f, glm::vec3(0, 1, 0));
	moonComposite->addTransformation(earthOrbit); 
	moonComposite->addTranslation(3.0f, 0.0f, 0.0f);
	moonComposite->addTransformation(moonEarthOrbit);
	moonComposite->addTranslation(0.8f, 0.0f, 0.0f);
	moonComposite->addScale(0.2f);

	moonObj->applyPhongShader();

	moonObj->onUpdate = [moonEarthOrbit](float deltaTime) {
		static float moonAngle = 0.0f;
		moonAngle += 8.0f * deltaTime; // 60 degrees per second
		if (moonAngle > 360.0f) moonAngle -= 360.0f;
		moonEarthOrbit->setAngle(moonAngle);
	};
	scene4->addObject(std::move(moonObj));

	auto sun = std::make_unique<PointLight>(
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.9f, 0.7f),  
		2.0f,
		0.0f
	);
	scene4->setLight(std::move(sun));

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

		auto camera = std::make_unique<Camera>(width, height);  
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

		if (currentSceneIndex == 2) { // forest scene
			auto& lights = scenes[currentSceneIndex]->getLights();
			for (auto& light : lights) {
				SpotLight* spot = dynamic_cast<SpotLight*>(light.get());
				if (spot) {
					Camera* camera = scenes[currentSceneIndex]->getCamera();
					spot->setPosition(camera->getPosition());
					spot->setDirection(camera->getFront());
				}
			}
		}

		// Vykreslení aktuální scény
		if (currentSceneIndex < scenes.size()) {
			scenes[currentSceneIndex]->draw(width,height);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}