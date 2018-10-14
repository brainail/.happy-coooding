#ifndef GCylinder_H_Included
#define GCylinder_H_Included

#include "GShape.h"
#include "GPoint.h"

class GCylinder: public GShape 
{
	public:
		GCylinder();
		virtual ~GCylinder();

		void Draw();

		void SetRadius(GLfloat aBaseRadius = 0.0f, GLfloat aTopRadius = 0.0f);
		void SetMeasure(GLfloat aLatitude = 10.0f, GLfloat aLongitude = 1.0f);
		void SetFromTo(GLfloat aFromX = 0.0f, GLfloat aFromY = 0.0f, GLfloat aFromZ = 0.0f, 
			          GLfloat aToX = 0.0f, GLfloat aToY = 0.0f, GLfloat aToZ = 0.0f);
		
	public:
		GLfloat baseRadius, topRadius;
		GLfloat latitude, longitude;
		GPoint from, to;

	public:
		GLUquadricObj * quadObj;
};

#endif 
