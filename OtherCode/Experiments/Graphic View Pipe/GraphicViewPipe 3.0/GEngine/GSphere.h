#ifndef GSphere_H_Included
#define GSphere_H_Included

#include "GShape.h"
#include "GPoint.h"

class GSphere: public GShape 
{
	public:
		GSphere();
		virtual ~GSphere();

		void Draw();

		void SetRadius(GLfloat aRadius = 0.0f);
		void SetMeasure(GLfloat aLatitude = 10.0f, GLfloat aLongitude = 10.0f);
		void SetCenter(GLfloat aX = 0.0f, GLfloat aY = 0.0f, GLfloat aZ = 0.0f);
		
	public:
		GLfloat radius;
		GLfloat latitude, longitude;
		GPoint center;

	public:
		GLUquadricObj * quadObj;
};

#endif 
