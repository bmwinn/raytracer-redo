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
	float intersect(Ray *ray, Point *point);
	void blinnPhong(Ray *ray, float rayDistance, Pigment *pixelPigment, Light *light, Camera *camera, 
	    vector<Geometry *> *allGeometry);
	// void blinnPhong(Ray *ray, float rayDist);

	void setVectors();
	void setNormal(Ray *ray);

	Point vertexA, vertexB, vertexC;
	Vector AB, AC;
};

#endif