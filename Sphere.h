#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Geometry.h"

/* Child of Geometry, contains center Point and radius value */
class Sphere : public Geometry {
public:
	Sphere();
	Sphere(Point center, float radius, Vector *normal, Pigment *pigment, Finish *finish);
	void print();
	void printType();
	float intersect(int pw, int ph, Ray ray);
	Pigment blinnPhong(int pw, int ph, Ray ray, float rayDistance, Point surface, Vector normal);

	void setCenter(Point c);
	void setRadius(float r);

	Point getCenter();
	float getRadius();
	Vector getNormal(Point surface, Ray ray);

private:
	Point center;
	float radius;
};

#endif