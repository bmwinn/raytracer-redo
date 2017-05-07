#ifndef _PLANE_H_
#define _PLANE_H_

#include "Geometry.h"

/* Child of Geometry, inherits normal Vector and contains distance along normal Vecor */
class Plane : public Geometry {
public:
	Plane();
	Plane(float distance, Vector *normal, Pigment *pigment, Finish *finish);
	void print();
	void printType();
	float intersect(Ray *ray);
	void blinnPhong(Ray *ray, float rayDistance, Pigment *pixelPigment, Light *light, Camera *camera, vector<Geometry *> *allGeometry);

	void setOnGeom();
	void setDistance(float d);

	float getDistance();

private:
	float distance;
};

#endif