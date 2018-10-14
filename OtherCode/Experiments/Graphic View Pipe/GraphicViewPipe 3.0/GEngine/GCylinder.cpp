#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
#include "GCylinder.h"
#include "GVector3.h"

const GLfloat deepening = 0.1f;

void GCylinder::Draw()
{
    glPushMatrix();

	GLfloat Matrix[16];
    rotation.GetMatrix(Matrix);
    glMultMatrixf(Matrix);
    glTranslatef(position.x, position.y, position.z);

        // Draw Cylinder
        GVector3 vect;
        vect.x = to.x - from.x;
        vect.y = to.y - from.y;
        vect.z = to.z - from.z;

        GLfloat vectSize = sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
        GLfloat aX = acos(vect.x / vectSize);
        GLfloat aY = acos(vect.y / vectSize);
        GLfloat aZ = acos(vect.z / vectSize);

        aX *= 180.0f / M_PI;
        aY *= -180.0f / M_PI;
        aZ *= 180.0f / M_PI;

        gluQuadricDrawStyle(quadObj, GLU_FILL);
        glTranslated(from.x, from.y, from.z);
        glRotated(-aZ, vect.y, -vect.x, 0);

        gluCylinder(quadObj, baseRadius, topRadius, vectSize + deepening, latitude, longitude);

    glPopMatrix();
}

void GCylinder::SetRadius(GLfloat aBaseRadius, GLfloat aTopRadius)
{
	baseRadius = aBaseRadius, topRadius = aTopRadius;
}

void GCylinder::SetMeasure(GLfloat aLatitude, GLfloat aLongitude)
{
	latitude = aLatitude, longitude = aLongitude;
}

void GCylinder::SetFromTo(GLfloat aFromX, GLfloat aFromY, GLfloat aFromZ, GLfloat aToX, GLfloat aToY, GLfloat aToZ)
{
	from.SetPosition(aFromX, aFromY, aFromZ);
	to.SetPosition(aToX, aToY, aToZ);
}

GCylinder::GCylinder()
{
	quadObj = gluNewQuadric();
}

GCylinder::~GCylinder()
{
	gluDeleteQuadric(quadObj);
}
