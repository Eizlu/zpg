#include "application.h"
#include <iostream>
#include "tree.h"
#include "sphere.h"
#include "suzi_flat.h"


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
			std::cout << "Switching to Scene 1 (Trees)" << std::endl;
			app->switchToScene(0);
		}
		else if (key == GLFW_KEY_2 || key == GLFW_KEY_KP_2) {
			std::cout << "Switching to Scene 2 (Spheres)" << std::endl;
			app->switchToScene(1);
		}
		else if (key == GLFW_KEY_3 || key == GLFW_KEY_KP_3) {
			std::cout << "Switching to Scene 3 (Mixed)" << std::endl;
			app->switchToScene(2);
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
	printf("cursor_callback \n"); 
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
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

void Application::createScenes()
{
	auto scene1 = std::make_unique<Scene>("Tree Scene");

	auto tree1 = new DrawableObject(new Model(tree, sizeof(tree) / sizeof(tree[0])));
	auto composite1 = tree1->createCompositeTransformation();
	composite1->createAndAddTransformation()->setPosition(-0.8f, -0.8f, 0.0f);
	composite1->createAndAddTransformation()->setScale(0.1f);
	scene1->addObject(tree1);

	auto tree2 = new DrawableObject(new Model(tree, sizeof(tree) / sizeof(tree[0])));
	auto composite2 = tree2->createCompositeTransformation();
	composite2->createAndAddTransformation()->setPosition(0.0f, -0.8f, 0.0f);
	composite2->createAndAddTransformation()->setRotation(45.0f, glm::vec3(0, 1, 0));
	composite2->createAndAddTransformation()->setScale(0.15f);
	scene1->addObject(tree2);

	auto tree3 = new DrawableObject(new Model(tree, sizeof(tree) / sizeof(tree[0])));
	auto composite3 = tree3->createCompositeTransformation();
	composite3->createAndAddTransformation()->setPosition(0.8f, -0.8f, 0.0f);
	composite3->createAndAddTransformation()->setRotation(30.0f, glm::vec3(0, 1, 0));
	composite3->createAndAddTransformation()->setScale(0.1f);
	scene1->addObject(tree3);

	scenes.push_back(std::move(scene1));

	auto scene2 = std::make_unique<Scene>("Sphere Scene");

	auto sphere1 = new DrawableObject(new Model(sphere, 17280));
	sphere1->getTransformation().setPosition(-0.5f, -0.5f, 0.0f);
	sphere1->getTransformation().setScale(0.2f);
	scene2->addObject(sphere1);

	auto sphere2 = new DrawableObject(new Model(sphere, 17280));
	sphere2->getTransformation().setPosition(0.5f, -0.5f, 0.0f);
	sphere2->getTransformation().setScale(0.2f);
	scene2->addObject(sphere2);

	auto sphere3 = new DrawableObject(new Model(sphere, 17280));
	sphere3->getTransformation().setPosition(0.5f, 0.5f, 0.0f);
	sphere3->getTransformation().setScale(0.2f);
	scene2->addObject(sphere3);

	auto sphere4 = new DrawableObject(new Model(sphere, 17280));
	sphere4->getTransformation().setPosition(-0.5f, 0.5f, 0.0f);
	sphere4->getTransformation().setScale(0.2f);
	scene2->addObject(sphere4);

	scenes.push_back(std::move(scene2));

	auto scene3 = std::make_unique<Scene>("Mixed Scene");

	auto treeObj = new DrawableObject(new Model(tree, sizeof(tree) / sizeof(tree[0])));
	treeObj->getTransformation().setPosition(-0.6f, -0.8f, 0.0f);
	treeObj->getTransformation().setScale(0.08f);
	scene3->addObject(treeObj);

	auto sphereObj = new DrawableObject(new Model(sphere, 17280));
	sphereObj->getTransformation().setPosition(0.6f, -0.3f, 0.0f);
	sphereObj->getTransformation().setRotation(90.0f, glm::vec3(1, 1, 0));
	sphereObj->getTransformation().setScale(0.2f);
	scene3->addObject(sphereObj);

	auto suziObj = new DrawableObject(new Model(suziFlat, sizeof(suziFlat) / sizeof(suziFlat[0])));
	suziObj->getTransformation().setPosition(-0.2f, 0.2f, 0.0f);
	suziObj->getTransformation().setRotation(-90.0f, glm::vec3(1, 0, 0));
	suziObj->getTransformation().setScale(0.5f);
	scene3->addObject(suziObj);

	scenes.push_back(std::move(scene3));
}

Application::Application(int width, int height, const char* title) : width(width), height(height), title(title), window(nullptr), currentSceneIndex(0)
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
	glfwSetWindowUserPointer(window, this);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "ERROR: could not initialize GLEW\n";
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);

	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	//glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);

	createScenes();
	auto mainCamera = new Camera();
	
	for (auto& scene:scenes) {
		scene->init();
		scene->setCamera(mainCamera);
		std::cout << "Initialized scene: " << scene->getName() << std::endl;
	}

	std::cout << "Application initialized with " << scenes.size() << " scenes" << std::endl;
	std::cout << "Controls: 1-" << scenes.size() << " - switch scenes "<< std::endl;
}

void Application::run()
{
	while (!glfwWindowShouldClose(window))
	{
		processInput();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Vykreslen� aktu�ln� sc�ny
		if (currentSceneIndex < scenes.size()) {
			scenes[currentSceneIndex]->draw();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}