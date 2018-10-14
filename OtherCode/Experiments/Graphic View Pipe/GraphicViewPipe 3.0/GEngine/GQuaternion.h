#ifndef GQuaternion_H_Included
#define GQuaternion_H_Included

#include "GVector3.h"

class GQuaternion
{
	public:
  	     GQuaternion();
		GQuaternion(GLfloat aX, GLfloat aY, GLfloat aZ, GLfloat aW);
	     GQuaternion(const GVector3 & v, GLfloat aW);
    	     virtual ~GQuaternion();

    		void Normalise();
    		void FromAxis(const GVector3 & v, GLfloat angle);
   		void FromEuler(GLfloat pitch, GLfloat yaw, GLfloat roll);
   		void GetAxisAngle(GVector3 * axis, GLfloat * angle);
   		GQuaternion GetConjugate();
    		void GetMatrix(GLfloat * matrix);

    		GQuaternion operator * (const GQuaternion & r);
   	     GVector3 operator * (const GVector3 & v);

	public:
    		GLfloat x, y, z, w;
};

#endif 
