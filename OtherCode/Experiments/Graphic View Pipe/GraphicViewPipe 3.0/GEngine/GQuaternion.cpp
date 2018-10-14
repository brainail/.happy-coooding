#include "GQuaternion.h"
#include <cmath>

const GLfloat PIOVER180 = M_PI / 180.0f;
const GLfloat EPS = 1e-7;

// normalising a quaternion works similar to a vector. This method will not do anything
// if the quaternion is close enough to being unit-length. define EPS as something
// small like 1e-7f to get accurate results
void GQuaternion::Normalise()
{
	GLfloat val = w * w + x * x + y * y + z * z;
	if (fabs(val) > EPS && fabs(val - 1.0f) > EPS) {
		val = sqrt(val);
		w /= val;
		x /= val;
		y /= val;
		z /= val;
	}
}

// We need to get the inverse of a quaternion to properly apply a quaternion-rotation to a vector
// The conjugate of a quaternion is the same as the inverse, as long as the quaternion is unit-length
GQuaternion GQuaternion::GetConjugate()
{
	return GQuaternion(-x, -y, -z, w);
}

// Multiplying q1 with q2 applies the rotation q2 to q1
GQuaternion GQuaternion::operator * (const GQuaternion & r)
{
	// the constructor takes its arguments as (x, y, z, w)
	return GQuaternion(w * r.x + x * r.w + y * r.z - z * r.y,
	                   w * r.y + y * r.w + z * r.x - x * r.z,
	                   w * r.z + z * r.w + x * r.y - y * r.x,
	                   w * r.w - x * r.x - y * r.y - z * r.z);
}

// Multiplying a quaternion q with a vector v applies the q-rotation to v
GVector3 GQuaternion::operator * (const GVector3 & v)
{
	GVector3 newV( v );
	//newV.Normalise();

	GQuaternion vecQuat, resQuat;
	vecQuat.x = newV.x;
	vecQuat.y = newV.y;
	vecQuat.z = newV.z;
	vecQuat.w = 0.0f;

	resQuat = vecQuat * GetConjugate();
	resQuat = *this * resQuat;

	return GVector3(resQuat.x, resQuat.y, resQuat.z);
}

// Convert from Axis Angle
void GQuaternion::FromAxis(const GVector3 & v, GLfloat angle)
{
	float sinAngle;
	angle *= 0.5f;
	GVector3 newV( v );
	newV.Normalise();

	sinAngle = sin(angle);

	x = newV.x * sinAngle;
	y = newV.y * sinAngle;
	z = newV.z * sinAngle;
	w = cos(angle);
}

// Convert from Euler Angles
void GQuaternion::FromEuler(GLfloat pitch, GLfloat yaw, GLfloat roll)
{
	// Basically we create 3 Quaternions, one for pitch, one for yaw, one for roll
	// and multiply those together.
	// the calculation below does the same, just shorter
	GLfloat p = pitch * PIOVER180 / 2.0;
	GLfloat y = yaw * PIOVER180 / 2.0;
	GLfloat r = roll * PIOVER180 / 2.0;

	GLfloat sinp = sin(p);
	GLfloat siny = sin(y);
	GLfloat sinr = sin(r);
	GLfloat cosp = cos(p);
	GLfloat cosy = cos(y);
	GLfloat cosr = cos(r);

	this->x = sinr * cosp * cosy - cosr * sinp * siny;
	this->y = cosr * sinp * cosy + sinr * cosp * siny;
	this->z = cosr * cosp * siny - sinr * sinp * cosy;
	this->w = cosr * cosp * cosy + sinr * sinp * siny;

	Normalise();
}

// Convert to Matrix
void GQuaternion::GetMatrix(GLfloat * matrix)
{
    if(!matrix) return;

	GLfloat x2 = x * x;
	GLfloat y2 = y * y;
	GLfloat z2 = z * z;
	GLfloat xy = x * y;
	GLfloat xz = x * z;
	GLfloat yz = y * z;
	GLfloat wx = w * x;
	GLfloat wy = w * y;
	GLfloat wz = w * z;

	// This calculation would be a lot more complicated for non-unit length quaternions
	matrix[ 0] = 1.0f - 2.0f * (y2 + z2);
	matrix[ 1] = 2.0f * (xy - wz);
	matrix[ 2] = 2.0f * (xz + wy);
	matrix[ 3] = 0.0f;

	matrix[ 4] = 2.0f * (xy + wz);
	matrix[ 5] = 1.0f - 2.0f * (x2 + z2);
	matrix[ 6] = 2.0f * (yz - wx);
	matrix[ 7] = 0.0f;

	matrix[ 8] = 2.0f * (xz - wy);
	matrix[ 9] = 2.0f * (yz + wx);
	matrix[10] = 1.0f - 2.0f * (x2 + y2);
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
}

// Convert to Axis Angles
void GQuaternion::GetAxisAngle(GVector3 * axis, GLfloat * angle)
{
	GLfloat scale = sqrt(x * x + y * y + z * z);
	axis->x = x / scale;
	axis->y = y / scale;
	axis->z = z / scale;
	*angle = acos(w) * 2.0f;
}

GQuaternion::~GQuaternion()
{
}

GQuaternion::GQuaternion()
{
    x = y = z = 0.0f, w = 1.0f;
}

GQuaternion::GQuaternion(GLfloat aX, GLfloat aY, GLfloat aZ, GLfloat aW)
{
    x = aX, y = aY, z = aZ, w = aW;
}

GQuaternion::GQuaternion(const GVector3 & v, GLfloat aW)
{
    x = v.x, y = v.y, z = v.z, w = aW;
}
