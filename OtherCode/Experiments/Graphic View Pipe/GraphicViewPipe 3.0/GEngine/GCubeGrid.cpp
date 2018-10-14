#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include "GCubeGrid.h"

const GLfloat EPS = 1e-7;

void GCubeGrid::Draw()
{
    glPushMatrix();

	GLfloat Matrix[16];
    rotation.GetMatrix(Matrix);
    glMultMatrixf(Matrix);
    glTranslatef(position.x, position.y, position.z);

    // Draw Grid using lines
    for (double i = -size; i <= size + EPS; i += 2.0f * size / measure)
        for (double j= -size; j <= size + EPS; j += 2.0f * size / measure)
        {
            glColor4d(color.r, color.g, color.b, color.alpha);

            glBegin(GL_LINES);
                glVertex3d(i, j, -size);
                glVertex3d(i, j, size);

                glVertex3d(i, -size, j);
                glVertex3d(i, size, j);

                glVertex3d(-size, i, j);
                glVertex3d(size, i, j);
            glEnd();
        }

   	glPopMatrix();
}

void GCubeGrid::SetSize(GLfloat aSize)
{
	size = aSize;
}

void GCubeGrid::SetMeasure(GLfloat aMeasure)
{
	measure = aMeasure;
}

GCubeGrid::~GCubeGrid()
{
}
