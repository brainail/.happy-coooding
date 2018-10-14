#include "GCamera.h"

const GLfloat GCamera::cameraSpeed;

void GCamera::SetView()
{
    GLfloat Matrix[16];
    rotation.GetMatrix(Matrix);
    glMultMatrixf(Matrix);
    glTranslatef(-position.x, -position.y, -position.z);
}

void GCamera::UpdatePosition(const bool keyDown[])
{
    if(keyDown[ 'a' ]) MoveX(-cameraSpeed);
    if(keyDown[ 'd' ]) MoveX(+cameraSpeed);
    if(keyDown[ 's' ]) MoveZ(-cameraSpeed);
    if(keyDown[ 'w' ]) MoveZ(+cameraSpeed);
    if(keyDown[ 'j' ]) MoveY(-cameraSpeed);
    if(keyDown[ 'u' ]) MoveY(+cameraSpeed);
}

GCamera::~GCamera()
{
}
