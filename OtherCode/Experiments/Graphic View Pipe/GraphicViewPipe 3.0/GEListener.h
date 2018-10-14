#ifndef GELISTENER_H_INCLUDED
#define GELISTENER_H_INCLUDED

#include <GL\gl.h>
#include <GL\glut.h>

class GEListener
{
public:
    GEListener();
    virtual ~GEListener();

    virtual void DisplayFunc(void) = 0;
    virtual void ReshapeFunc(int width, int height) = 0;
    virtual void KeyboardFunc(unsigned char key, int x, int y) = 0;
    virtual void KeyboardUpFunc(unsigned char key, int x, int y) = 0;
    virtual void MouseFunc(int button, int state, int x, int y) = 0;
    virtual void MotionFunc(int x, int y) = 0;
    virtual void Initialize(void) = 0;
};

#endif // GELISTENER_H_INCLUDED
