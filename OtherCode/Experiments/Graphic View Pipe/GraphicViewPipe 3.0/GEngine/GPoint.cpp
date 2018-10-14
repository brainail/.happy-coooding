#include "GPoint.h"

GPoint::GPoint(GLfloat aX, GLfloat aY, GLfloat aZ)
{
	x = aX, y = aY, z = aZ;
}

void GPoint::SetPosition(GLfloat aX, GLfloat aY, GLfloat aZ)
{
	x = aX, y = aY, z = aZ;
}

GPoint::~GPoint()
{

}
