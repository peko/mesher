#pragma once

#include <GLFW/glfw3.h>

class Gui {
public:
    Gui(GLFWwindow* w);
    ~Gui();

    void background();
    void draw();
    void render();
    void shutdown();

private:
    GLFWwindow* window;
};