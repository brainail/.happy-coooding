#include "GVector3.h"
#include <cmath>

const GLfloat EPS = 1e-9;

void GVector3::Normalise()
{
	GLfloat val = x * x + y * y + z * z;
	if (fabs(val) > EPS && fabs(val - 1.0f) > EPS) {
		val = sqrt(val);
		x /= val;
		y /= val;
		z /= val;
	}
}

GVector3::GVector3()
{
	x = y = z = 0.0f;
}

GVector3::GVector3(GLfloat aX, GLfloat aY, GLfloat aZ)
{
	x = aX, y = aY, z = aZ;
}

GVector3::GVector3(const GVector3 & v)
{
    x = v.x, y = v.y, z = v.z;
}

void GVector3::operator *= (GLfloat scalar)
{
	x *= scalar, y *= scalar, z *= scalar;
}

void GVector3::operator += (GVector3 v)
{
	x += v.x, y += v.y, z += v.z;
}

GVector3::~GVector3()
{
}

