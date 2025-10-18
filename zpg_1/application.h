#pragma once
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include "scene.h"


class Application
{
	//inicializace okna a OpenGL
private:
	GLFWwindow* window;
	std::vector<std::unique_ptr<Scene>> scenes;
	//Camera* mainCamera;
	//std::unique_ptr<Camera> mainCamera;
	int currentSceneIndex;
	int width;
	int height;
	const char* title;

	bool rightMouseButtonPressed;
	double lastMouseX;
	double lastMouseY;

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void cursor_callback(GLFWwindow* window, double x, double y);
	static void button_callback(GLFWwindow* window, int button, int action, int mode);

	void createScenes();
	void generateForest(Scene* scene, int treeCount, int bushCount);
	void switchToScene(int index);
	void processInput();
public:
	Application(int width, int height, const char* title);
	~Application();
	void initialize();
	void run();
};