#include "application.h"
#include <iostream>


void Application::error_callback(int error, const char* description) {
	fputs(description, stderr);
}
void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) printf("key_callback [%d,%d,%d,%d]\n", key, scancode, action, mods);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

Application::Application(int width, int height, const char* title ) : width(width),height(height), title(title), window(nullptr)
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

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "ERROR: could not initialize GLEW\n";
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);
	
	scene.init();
}

void Application::run()
{
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene.draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}