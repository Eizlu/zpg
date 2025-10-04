#pragma once
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include "scene.h"


class Application
{
	//inicializace okna a OpenGL
private:
	GLFWwindow* window;
	Scene scene;
	int width;
	int height;
	const char* title;

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void window_size_callback(GLFWwindow* window, int width, int height);
public:
	Application(int width, int height, const char* title);
	~Application();
	void initialize();
	void run();
};