//Include GLEW
#include <GL/glew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>


float offsetX_t = -0.4f;
float offsetY_t = 0.4f;
float offsetX_s = +0.4f;
float offsetY_s = -0.4f;
struct Vertex {
	float position[4]; // x, y, z, w
	float color[4];    // r, g, b, a
};

const Vertex b[] = {
	{{0.0f+ offsetX_t, 0.3f+ offsetY_t, 0.0f ,1.f},{ 0, 1, 0, 1 }},
	{{0.3f+ offsetX_t, -0.3f+ offsetY_t, 0.0, 1.f},{ 1, 0, 0, 1 }},
	{{ -0.3f+ offsetX_t, -0.3f+ offsetY_t, 0.0f, 1.f },{ 0, 0, 0, 1 }}
};

const Vertex square[] = {
	{{ -0.3f+ offsetX_s, 0.3f+ offsetY_s, 0.0f, 1.0f},{0,1,1,1}},
	{{0.3f+ offsetX_s, 0.3f+ offsetY_s, 0.0f, 1.0f},{0,0,0,1}},
	{{-0.3f+ offsetX_s,  -0.3f+ offsetY_s, 0.0f, 1.0f},{0,0,0,1}},

	{{0.3f+ offsetX_s,  0.3f+ offsetY_s, 0.0f, 1.0f},{0,0,0,1}},
	{{-0.3f+ offsetX_s, -0.3f+ offsetY_s, 0.0f, 1.0f},{0,0,0,1}},
	{{0.3f+ offsetX_s,  -0.3f+ offsetY_s, 0.0f, 1.0f},{1,0,1,1}}
};

//const a b[] = {
//   { { -.5f, -.5f, .5f, 1 }, { 1, 1, 0, 1 } },
//   { { -.5f, .5f, .5f, 1 }, { 1, 0, 0, 1 } },
//   { { .5f, .5f, .5f, 1 }, { 0, 0, 0, 1 } },
//   { { .5f, -.5f, .5f, 1 }, { 0, 1, 0, 1 } },
//};

const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec4 vp;" //vertex position
"layout(location=1) in vec4 color;"	//vertex color
"out vec4 vertexColor;" //output to fragment shader
"void main () {"
"	gl_Position = vp;"
"	vertexColor = color;"
"}";



const char* fragment_shader =
"#version 330\n"		
"in vec4 vertexColor;" //input from vertex shader
"out vec4 fragColor;"	//output  fragment color
"void main () {"
"	fragColor=vertexColor; "
"}";


//float angle = 0.0f;
//float baseSpeed = 50.0f;
//float speedChanger = 1.0f;
//int rotatingDir = 1;
//bool rotateAroundCorner = false;
//
//glm::vec3 rotateAxis(0.f, 0.f, 1.f);
//
//


static void error_callback(int error, const char* description) { fputs(description, stderr); }

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	/*if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		rotatingDir *= -1;
	if (key == GLFW_KEY_UP)
	{
		if (action == GLFW_PRESS)
			speedChanger = 2.0f;
		else if (action == GLFW_RELEASE)
			speedChanger = 1.0f;
	}
	if (key == GLFW_KEY_DOWN)
	{
		if (action == GLFW_PRESS)
			speedChanger = 0.5f;
		else if (action == GLFW_RELEASE)
			speedChanger = 1.0f;
	}
	if(key == GLFW_KEY_X && action == GLFW_PRESS)
		rotateAxis = glm::vec3(1, 0, 0);
	if (key == GLFW_KEY_Y && action == GLFW_PRESS)
		rotateAxis = glm::vec3(0, 1, 0);
	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
		rotateAxis = glm::vec3(0, 0, 1);

	if (key == GLFW_KEY_C && action == GLFW_PRESS)
		rotateAroundCorner = !rotateAroundCorner;
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);*/
}

static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

static void cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

static void button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}



/*
//GLM test

// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

// Camera matrix
glm::mat4 View = glm::lookAt(
	glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
	glm::vec3(0, 0, 0), // and looks at the origin
	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
);
// Model matrix : an identity matrix (model will be at the origin)
glm::mat4 Model = glm::mat4(1.0f);
*/


int main(void)
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	/* //inicializace konkretni verze
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
	GLFW_OPENGL_CORE_PROFILE);  //*/

	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	//// Sets the key callback
	//glfwSetKeyCallback(window, key_callback);

	//glfwSetCursorPosCallback(window, cursor_callback);

	//glfwSetMouseButtonCallback(window, button_callback);

	//glfwSetWindowFocusCallback(window, window_focus_callback);

	//glfwSetWindowIconifyCallback(window, window_iconify_callback);

	//glfwSetWindowSizeCallback(window, window_size_callback);


	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);


	//vertex buffer object (VBO)
	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(b), b, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0); //enable vertex attributes

	// color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 4));
	glEnableVertexAttribArray(1);

	GLuint VBO_square, VAO_square;

	glGenBuffers(1, &VBO_square);
	glGenVertexArrays(1, &VAO_square);

	glBindVertexArray(VAO_square);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_square);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 4));
	glEnableVertexAttribArray(1);

	//unbinding
	glBindVertexArray(0);


	//create and compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	while (!glfwWindowShouldClose(window))
	{
		//glClear(GL_COLOR_BUFFER_BIT);

		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();

		//static double lastTime = glfwGetTime();
		//double currentTime = glfwGetTime();
		//double deltaTime = currentTime - lastTime;
		//lastTime = currentTime;
		//angle += rotatingDir * (baseSpeed * speedChanger) * (float)deltaTime;

		//if (rotateAroundCorner)
		//{
		//	glTranslatef(-0.6f, 0.6f, 0.f);

		//	glRotatef(angle, rotateAxis.x, rotateAxis.y, rotateAxis.z);

		//	glTranslatef(-0.6f, 0.6f, 0.f);

		//}
		//else
		//{
		//	glRotatef(angle, rotateAxis.x, rotateAxis.y, rotateAxis.z);
		//}

		///*glBegin(GL_TRIANGLES);
		//glColor3f(1.f, 0.f, 0.f);
		//glVertex3f(-0.6f, -0.4f, 0.f);
		//glColor3f(0.f, 1.f, 0.f);
		//glVertex3f(0.6f, -0.4f, 0.f);
		//glColor3f(0.f, 0.f, 1.f);
		//glVertex3f(0.f, 0.6f, 0.f);
		//glEnd();*/

		//glBegin(GL_QUADS);
		//glColor3f(1.f, 0.f, 0.f); // red
		//glVertex3f(-0.6f, 0.6f, 0.f); //levy vrchni
		//glColor3f(1.f, 1.f, 0.f); // zluta  ( R + G)
		//glVertex3f(0.6f, 0.6f, 0.f); //pravy vrchni
		//glColor3f(0.f, 1.f, 0.f); // green
		//glVertex3f(0.6f, -0.6f, 0.f); //pravy spodni
		//glColor3f(0.f, 0.f, 1.f); // modra
		//glVertex3f(-0.6f, -0.6f, 0.f); //levy spodni
		//glEnd();

		//glfwSwapBuffers(window);

		//glfwPollEvents();

		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// draw triangles
		glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count
		// draw square
		glBindVertexArray(VAO_square);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}