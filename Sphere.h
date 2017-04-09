#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Geometry.h"

/* Child of Geometry, contains center Point and radius value */
class Sphere : public Geometry {
public:
	Sphere();
	Sphere(Point center, float radius, Vector *normal, Pigment *pigment, Finish *finish);
	void Print();
	float Intersect(Ray *ray, Camera *camera);

	void setCenter(Point *c);
	void setRadius(float r);

	Point *getCenter();
	float getRadius();

private:
	Point center;
	float radius;
};

#endif