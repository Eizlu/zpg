/**
 * @file main.cpp
 *
 * @brief Main function
 *
 * @author Česlárová Eliška CES0022
  **/

#include "application.h"




int main() {
    // Pass width, height, title explicitly
    Application* app = new Application(1200, 800, "ZPG");
    app->initialize();
    app->run();
    delete app;
    return 0;
}