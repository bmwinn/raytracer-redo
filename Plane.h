#ifndef _PLANE_H_
#define _PLANE_H_

#include "Geometry.h"

/* Child of Geometry, inherits normal Vector and contains distance along normal Vecor */
class Plane : public Geometry {
public:
	Plane();
	Plane(float distance, Vector normal, Pigment pigment, Finish finish);
	void print();
	void printType();
	float intersect(int pw, int ph, Ray ray);
	Pigment blinnPhong(int pw, int ph, Ray ray, float rayDistance, Point surface, Vector normal);

	void setDistance(float d);
	void setNorm(Vector n);

	float getDistance();
	Vector getNormal(Point surface, Ray ray);
	Vector getNorm();

private:
	Vector norm;
	float distance;
};

#endif