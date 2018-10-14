#include "GObject.h"
#include <cmath>

const GLfloat PIOVER180 = M_PI / 180.0;

void GObject::MoveX(GLfloat shiftX)
{
	position += rotation * GVector3(shiftX, 0.0f, 0.0f);
}

void GObject::MoveY(GLfloat shiftY)
{
	position += rotation * GVector3(0.0f, shiftY, 0.0f);
}

void GObject::MoveZ(GLfloat shiftZ)
{
	position += rotation * GVector3(0.0f, 0.0f, -shiftZ);
}

void GObject::RotateY(GLfloat angleY)
{
    GQuaternion newRotation;
    newRotation.FromAxis(GVector3(1.0f, 0.0f, 0.0f), angleY * PIOVER180);
    rotation = rotation * newRotation;
}

void GObject::RotateX(GLfloat angleX)
{
    GQuaternion newRotation;
    newRotation.FromAxis(GVector3(0.0f, 1.0f, 0.0f), angleX * PIOVER180);
    rotation = newRotation * rotation;
}

GObject::~GObject()
{
}
