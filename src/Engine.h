#pragma once

#include <sstream>

class Gui;
class EsriShape;
class GLFWwindow;

using namespace std;

class Engine {
public:

    ostringstream status;
    
    Engine();
    ~Engine();

    GLFWwindow* window;
    Gui* gui;
    EsriShape* shape;
    void loop();
};

