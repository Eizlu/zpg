/**
 * @file main.cpp
 *
 * @brief Main function
 *
 * @author Česlárová Eliška CES0022
  **/

#include "application.h"




//static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }
//
//static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }
//
//static void cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }
//
//static void button_callback(GLFWwindow* window, int button, int action, int mode) {
//	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
//}


int main() {
    // Pass width, height, title explicitly
    Application* app = new Application(800, 600, "ZPG");
    app->initialize();
    app->run();
    delete app;
    return 0;
}