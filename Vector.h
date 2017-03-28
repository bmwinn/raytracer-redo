#ifndef _VECTOR_H_
#define _VECTOR_H_

class Vector {
public:
	Vector();
	Vector(float x, float y, float z);
	float Dot(Vector *other);
	void Cross(Vector *other, Vector *result);
	void SetMagnitude(float x, float y, float z);
	void Normalize();
	float x, y, z, magnitude;
};

#endif