#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cmath>

class Vector {
public:
	Vector();
	Vector(float x, float y, float z);
	float dot(Vector *other);
	void cross(Vector *other, Vector *result);
	void normalize();

	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setMagnitude(float x, float y, float z);

	float getX();
	float getY();
	float getZ();
	float getMagnitude();

private:
	float x, y, z, magnitude;
};

#endif