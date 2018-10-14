#ifndef GVector3_H_Included
#define GVector3_H_Included

#include <gl\gl.h>

class GVector3
{
	public:
		GVector3();
		GVector3(GLfloat aX, GLfloat aY, GLfloat aZ);
		GVector3(const GVector3 & v);
		virtual ~GVector3();

    		void Normalise();

    		void operator *= (GLfloat scalar);
    		void operator += (GVector3 v);

	public:
		GLfloat x, y, z;
};

#endif
