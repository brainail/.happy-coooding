#include "GERunner.h"

GEListener* GERunner::listener;
GERunner* GERunner::_instance = 0;

GERunner* GERunner::Instance()
{
    if (_instance == 0)
    {
        _instance = new GERunner();
    }
    return _instance;
}

void GERunner::Release()
{
    delete _instance;
    _instance = 0;
}

void GERunner::Initialize(int argc, char **argv)
{
    glutInit(&argc, argv);
}

void GERunner::GECreateWindow(GLuint displayMode, GERunner::Position position, GERunner::Size size, const char* title)
{
    glutInitDisplayMode(displayMode);
    glutInitWindowPosition(position.x, position.y);
    glutInitWindowSize(size.width, size.height);
    glutCreateWindow(title);
}

void GERunner::SetEventListener(GEListener *listener)
{
    this->listener = listener;
}

void GERunner::Prepare(void)
{
    glutDisplayFunc(this->DisplayFunc);
    glutKeyboardFunc(this->KeyboardFunc);
    glutKeyboardUpFunc(this->KeyboardUpFunc);
    glutMotionFunc(this->MotionFunc);
    glutMouseFunc(this->MouseFunc);
    glutReshapeFunc(this->ReshapeFunc);

    GERunner::listener->Initialize();
}

void GERunner::Run(void)
{
    glutMainLoop();
}

GERunner::GERunner()
{
    this->listener = NULL;
}

GERunner::~GERunner()
{
    if (listener)
        delete listener;
    listener = NULL;
}

void GERunner::DisplayFunc(void)
{
    if (listener)
        listener->DisplayFunc();
}

void GERunner::ReshapeFunc(int width, int height)
{
    if (listener)
        listener->ReshapeFunc(width, height);
}

void GERunner::KeyboardFunc(unsigned char key, int x, int y)
{
    if (listener)
        listener->KeyboardFunc(key, x, y);
}

void GERunner::KeyboardUpFunc(unsigned char key, int x, int y)
{
    if (listener)
        listener->KeyboardUpFunc(key, x, y);
}

void GERunner::MotionFunc(int x, int y)
{
    if (listener)
        listener->MotionFunc(x, y);
}

void GERunner::MouseFunc(int button, int state, int x, int y)
{
    if (listener)
        listener->MouseFunc(button, state, x, y);
}
