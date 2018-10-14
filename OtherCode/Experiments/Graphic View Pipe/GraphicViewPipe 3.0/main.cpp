#include <windows.h>
#include <gl\glut.h>

#include "GERunner.h"
#include "GEListenerImpl.h"

int main(int argc, char **argv)
{
    GERunner * geRunner = GERunner::Instance();
    GEListenerImpl * geListener = new GEListenerImpl();

    geRunner->Initialize(argc, argv);
    geRunner->SetEventListener(geListener);
    geRunner->GECreateWindow(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA,
                             GERunner::Position(100, 100),
                             GERunner::Size(640, 480),
                             "NewWindow");
    geRunner->Prepare();
    geRunner->Run();

    delete geListener;
    geRunner->Release();

    return 0;
}

