#include <stdio.h>
#include <iostream>

#include "Engine.h"

#include "Gui.h"
#include "EsriShape.h"

using namespace std;

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error %d: %s\n", error, description);
}


Engine::Engine(){
    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) throw "GLFW initializacition ERROR";

    window = glfwCreateWindow(1280, 720, "shape mesher", NULL, NULL);
    glfwMakeContextCurrent(window);

    gui   = new Gui(this);
    
    shape = new EsriShape();
    shape->load("data/110m");

    status << "GLFW "
           << GLFW_VERSION_MAJOR << "."
           << GLFW_VERSION_MINOR << "."
           << GLFW_VERSION_REVISION << endl;

    status << "GL_VERSION "
           << glGetString(GL_VERSION) << endl;
}


Engine::~Engine() {
    delete gui;
    delete shape;

    glfwTerminate();
}

void Engine::loop() {
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        gui->draw();
        gui->background();

        shape->draw(window);

        gui->render();
        glfwSwapBuffers(window);
    }
}
