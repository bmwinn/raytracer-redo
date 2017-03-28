#ifndef _PLANE_H_
#define _PLANE_H_

#include "Geometry.h"
// #include "Vector.h"
// #include "Camera.h"

/* Child of Geometry, inherits normal Vector and contains distance along normal Vecor */
class Plane : public Geometry {
public:
	Plane();
	Plane(Vector normal, float distance, Pigment pigment, Finish finish);
	void Print();
	float Intersect(Ray *ray, Camera *camera);
	float distance;
};

#endif