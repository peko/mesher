#pragma once

#include <string>

class Engine;

class Gui {
public:
    
    Engine* engine;

    Gui(Engine* e);
    ~Gui();

    void background();
    void draw();
    void render();

 };
