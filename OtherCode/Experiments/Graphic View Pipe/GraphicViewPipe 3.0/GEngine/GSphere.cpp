#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include "GSphere.h"

void GSphere::Draw()
{
    glPushMatrix();

	GLfloat Matrix[16];
    rotation.GetMatrix(Matrix);
    glMultMatrixf(Matrix);
    glTranslatef(position.x, position.y, position.z);

          // Draw Sphere
          gluQuadricDrawStyle(quadObj, GLU_FILL);
      	  glTranslated(center.x, center.y, center.z);
       	  gluSphere(quadObj, radius, latitude, longitude);

    	glPopMatrix();
}

void GSphere::SetRadius(GLfloat aRadius)
{
	radius = aRadius;
}

void GSphere::SetMeasure(GLfloat aLatitude, GLfloat aLongitude)
{
	latitude = aLatitude, longitude = aLongitude;
}

void GSphere::SetCenter(GLfloat aX, GLfloat aY, GLfloat aZ)
{
	center.SetPosition(aX, aY, aZ);
}

GSphere::GSphere()
{
	quadObj = gluNewQuadric();
}

GSphere::~GSphere()
{
	gluDeleteQuadric(quadObj);
}
