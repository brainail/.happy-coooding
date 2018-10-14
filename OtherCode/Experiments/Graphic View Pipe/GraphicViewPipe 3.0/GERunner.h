#ifndef GERUNNER_H_INCLUDED
#define GERUNNER_H_INCLUDED

#include "GEListener.h"

class GERunner
{
private:
    static GEListener *listener;
    static GERunner* _instance;
    static void DisplayFunc(void);
    static void KeyboardFunc(unsigned char key, int x, int y);
    static void KeyboardUpFunc(unsigned char key, int x, int y);
    static void MotionFunc(int x, int y);
    static void MouseFunc(int button, int state, int x, int y);
    static void ReshapeFunc(int width, int height);
    ~GERunner();
protected:
    GERunner();
public:

    struct Position
    {
        GLuint x, y;
        Position(GLuint _x = 0, GLuint _y = 0) : x(_x), y(_y) {}
    };

    struct Size
    {
        GLuint width, height;
        Size(GLuint _width = 1, GLuint _height = 1) : width(_width), height(_height) {}
    };

    static GERunner* Instance();

    void Initialize(int argc, char **argv);
    void GECreateWindow(GLuint displayMode, Position position, Size size, const char* title);
    void SetEventListener(GEListener *listener);
    void Prepare(void);
    void Run(void);
    void Release(void);
};

#endif // GERUNNER_H_INCLUDED
