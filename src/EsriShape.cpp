#include <iostream>
#include <shapefil.h>

#include "EsriShape.h"

using  namespace std;

void EsriShape::load(string path) {

    cerr << "Load: " << path << endl;

    SHPHandle shp_h = SHPOpen(path.c_str(), "rb");
    if(shp_h == NULL) {
        cerr << "ERROR LOADING" << path << endl;
        return;
    }

    {
        double minBound[4], maxBound[4];
        int shapes_count, shapes_type;

        SHPGetInfo(shp_h, &shapes_count, &shapes_type, minBound, maxBound);

        cerr << "Shapes: " << shapes_count << endl;
        cerr << "Type: " << shapes_type << endl;
        cerr << "Bounds: " << endl;

        for(int i=0; i<3; i++)
            cout << "\t" << i << ": " << minBound[i] << " - " << maxBound[i] << endl;

        for (int i = 0; i < shapes_count; ++i) {

            shapes.push_back(shape_t{});
            shape_t& shape = shapes.back();

            SHPObject* shp = SHPReadObject(shp_h, i);
            if(shp->nParts == 0) continue;

            if(shp->panPartStart[0] !=0 ) {
                cerr << "Something wrong with shape " << i << endl;
                continue;
            }
            int parts = shp->nParts;
            for (int j = 0; j < parts; ++j) {
                shape.push_back(contour_t{});
                contour_t& part = shape.back();
                int sid = shp->panPartStart[j];
                int eid = (j+1 < parts) ? shp->panPartStart[j+1] : shp->nVertices;
                for (int pid = sid; pid < eid; ++pid) {
                    part.push_back(Point_2{shp->padfX[pid], shp->padfY[pid]});
                }
            }
        }
    }
    SHPClose(shp_h);

	// Загружаем DBF со значениями
    DBFHandle hDBF;
    hDBF = DBFOpen(path.c_str(), "rb" );
    if( hDBF == NULL ) {
        cerr <<  "DBFOpen FAILED " << path << "\n";
        return;
    }
    int fid = DBFGetFieldIndex(hDBF, "long_name");
    for(int i = 0; i < DBFGetRecordCount(hDBF); i++ ) {
        char* str = (char *) DBFReadStringAttribute(hDBF, i, fid);
		if(str != NULL) names.push_back(str);
		else names.push_back("-");
    }
    DBFClose( hDBF );
}

void EsriShape::draw(GLFWwindow *window) {
    // Drawable::draw(window);

    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

    for(auto& shape : shapes) {
        for(auto& part : shape) {
            glBegin(GL_LINE_STRIP);
            for(auto& pnt : part) {
                glColor3f(1.f, 1.f, 1.f);
                glVertex3f(pnt[0]/180.0f, pnt[1]/90.f, 1.f);
            }
            glEnd();
        }
    }
}

void EsriShape::convexHull() {

}

