#pragma once

#include <string>
#include <GLFW/glfw3.h>

class Gui {
public:
    Gui(GLFWwindow *w);
    ~Gui();

    std::string status;

    void background();
    void draw();
    void render();
    void shutdown();

private:
    GLFWwindow* window;
 };