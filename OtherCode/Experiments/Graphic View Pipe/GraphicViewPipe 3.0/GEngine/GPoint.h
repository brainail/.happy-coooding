#ifndef GPoint_H_INCLUDED
#define GPoint_H_INCLUDED

#include <gl\gl.h>

class GPoint
{
	public:
		GPoint(GLfloat aX = 0.0f, GLfloat aY = 0.0f, GLfloat aZ = 0.0f);
		virtual ~GPoint();

		void SetPosition(GLfloat aX = 0.0f, GLfloat aY = 0.0f, GLfloat aZ = 0.0f);

	public:
		GLfloat x, y, z;
};

#endif
