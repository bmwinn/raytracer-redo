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
	Pigment blinnPhong(int pw, int ph, Ray *ray, float rayDistance, Point surface);

	void setVectors();
	void setNormal(Ray *ray);

	void setVertexA(Point vA);
	void setVertexB(Point vB);
	void setVertexC(Point vC);
	void setAB(Vector ab);
	void setAC(Vector ac);

	Point *getVertexA();
	Point *getVertexB();
	Point *getVertexC();
	Vector *getAB();
	Vector *getAC();

private:
	Point vertexA, vertexB, vertexC;
	Vector AB, AC;
};

#endif