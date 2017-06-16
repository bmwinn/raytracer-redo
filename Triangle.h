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
	Triangle(Point vA, Point vB, Point vC, Pigment pigment, Finish finish);
	void print();
	void printType();
	float intersect(int pw, int ph, Ray ray);
	Pigment blinnPhong(int pw, int ph, Ray ray, float rayDistance, Point surface, Vector normal);

	void setVectors();

	void setVertexA(Point vA);
	void setVertexB(Point vB);
	void setVertexC(Point vC);
	void setAB(Vector ab);
	void setAC(Vector ac);

	Point getVertexA();
	Point getVertexB();
	Point getVertexC();
	Vector getAB();
	Vector getAC();
	Vector getNormal(Point surface, Ray ray);

private:
	Point vertexA, vertexB, vertexC;
	Vector AB, AC;
};

#endif