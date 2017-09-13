#pragma once

#include <string>
#include <vector>

#include <GLFW/glfw3.h>
#include "./Drawable.h"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;

using namespace std;

// Обертка вокруг shapelib
// Шейп состоит из частей
// Часть состоит из точек

typedef vector<Point_2> contour_t;
typedef vector<contour_t> shape_t;

class EsriShape : public Drawable {

public:

    vector<shape_t> shapes;
    vector<string> names;

    void load(string path);

    virtual void draw(GLFWwindow *window) override;

    void convexHull();
};
