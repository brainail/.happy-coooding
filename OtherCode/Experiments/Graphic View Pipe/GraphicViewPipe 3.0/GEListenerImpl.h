#ifndef GELISTENERIMPL_H_INCLUDED
#define GELISTENERIMPL_H_INCLUDED

#include "GEListener.h"
#include "GEngine\GCamera.h"
#include "GEngine\GCubeGrid.h"
#include "GEngine\GPoint.h"
#include "GEngine\GSphere.h"
#include "GEngine\GCylinder.h"

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class GEListenerImpl : public GEListener
{
private:
    GCamera * gCamera;
    GCubeGrid * gGrid;
    GSphere * gSphere;
    GCylinder * gCylinder;
    bool keyDown[256];
    int mousePX, mousePY, mouseX, mouseY, n;
    vector<GPoint> points;
    GLfloat gridSize;
    bool rightMouseClick;

public:
    GEListenerImpl();
    virtual ~GEListenerImpl();

    void DisplayFunc(void);
    void ReshapeFunc(int width, int height);
    void KeyboardFunc(unsigned char key, int x, int y);
    void KeyboardUpFunc(unsigned char key, int x, int y);
    void MouseFunc(int button, int state, int x, int y);
    void MotionFunc(int x, int y);
    void Initialize(void);
};

#endif // GELISTENERIMPL_H_INCLUDED
