#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <iostream>

#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Pigment.h"
#include "Geometry.h"

using namespace std;

class Triangle : public Geometry {
public:
	Triangle();
	Triangle(Point *vA, Point *vB, Point *vC);
	void print();
	void printType();
	float intersect(Ray *ray);
	void blinnPhong(Ray *ray, float rayDistance);

	void setVectors();
	void setNormal(Ray *ray);

	Point vertexA, vertexB, vertexC;
	Vector AB, AC;
};

#endif