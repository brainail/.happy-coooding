#ifndef GObject_H_Included
#define GObject_H_Included

#include "GQuaternion.h"
#include "GVector3.h"

class GObject
{
	public:
		virtual ~GObject();

        void MoveX(GLfloat shiftX);
		void MoveY(GLfloat shiftY);
		void MoveZ(GLfloat shiftZ);
		void RotateX(GLfloat angleX);
		void RotateY(GLfloat angleY);

	public:
		GQuaternion rotation;
		GVector3 position;
};

#endif
