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
	// add to vector:
	// vector = point - point;
	// vector = vector + vector

	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setMagnitude(float x, float y, float z);
	void setMagnitude(float magnitude);
	void setMagnitude(Vector *other);
	
	float getX();
	float getY();
	float getZ();
	float getMagnitude();

private:
	// make public
	float x, y, z, magnitude;
};

#endif