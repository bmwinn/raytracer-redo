#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cmath>
#include <iostream>

using namespace std;

class Vector {
public:
	Vector();
	Vector(float x, float y, float z);
	float dot(Vector *other);
	void cross(Vector *other, Vector *result);
	void normalize();
	void print();

	void operator*=(float scalar);
	Vector operator-(Vector other);
	Vector operator+(Vector other);

	void setMagnitude(float x, float y, float z);
	void setMagnitude(Vector *other);
	
	float x, y, z;
	float magnitude;
};

#endif