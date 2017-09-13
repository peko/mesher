#pragma once

#include <GLFW/glfw3.h>
// Реализует отрисовку 2D фигур
class Drawable {
public:
    virtual void draw(GLFWwindow *window);
    void create_vbo();
    void delete_vbo();
};
