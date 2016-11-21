#pragma once

#include <string>
#include <GLFW/glfw3.h>

using std::string;

class Shape {
public:
    Shape();

    void load(string path);
    void draw(GLFWwindow *window);
};