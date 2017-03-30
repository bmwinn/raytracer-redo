#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Geometry.h"

/* Child of Geometry, contains center Point and radius value */
class Sphere : public Geometry {
public:
	Sphere();
	Sphere(Point center, float radius, Pigment pigment, Finish finish);
	void Print();
	float Intersect(Ray *ray, Camera *camera);
	Point center;
	float radius;
};

#endif