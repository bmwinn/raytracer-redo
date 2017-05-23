#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>

#include "Vector.h"

using namespace std;

class Point {
public:
	Point();
	Point(float x, float y, float z);
	~Point();
	float distance(Point *other);
	void print();

	Vector operator-(Point other);
	Vector operator+(Point other);
	void operator+=(Vector other);

	float x, y, z;
};

#endif