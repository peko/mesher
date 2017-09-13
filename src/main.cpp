
#include <stdio.h>
#include <iostream>

#include <GLFW/glfw3.h>
#include <sstream>

#include "Gui.h"
#include "EsriShape.h"

using namespace std;

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error %d: %s\n", error, description);
}

int
main() {

    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) return 1;

    GLFWwindow* window = glfwCreateWindow(1280, 720, "shape mesher", NULL, NULL);
    glfwMakeContextCurrent(window);

    EsriShape shape;
    shape.load("data/110m");

    Gui gui(window);
    ostringstream status;
    status << "GLFW "
           << GLFW_VERSION_MAJOR << "."
           << GLFW_VERSION_MINOR << "."
           << GLFW_VERSION_REVISION << endl;

    status << "GL_VERSION "
           << glGetString(GL_VERSION) << endl;

    gui.status = status.str();

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        gui.draw();
        gui.background();

        shape.draw(window);

        gui.render();
        glfwSwapBuffers(window);
    }

    // Cleanup
    gui.shutdown();
    glfwTerminate();

    return 0;
}
