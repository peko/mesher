// ImGui - standalone example application for Glfw + OpenGL 2, using fixed pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

#include <stdio.h>
#include <GLFW/glfw3.h>

#include "gui.h"
#include "shape.h"

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error %d: %s\n", error, description);
}

int
main(int, char**) {

    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) return 1;

    GLFWwindow* window = glfwCreateWindow(1280, 720, "shape mesher", NULL, NULL);
    glfwMakeContextCurrent(window);

    Shape shape;
    shape.load("some_file.shp");
    Gui gui(window);

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
