#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "Vector.h"
#include "Pigment.h"
#include "Finish.h"
#include "Ray.h"
#include "Camera.h"

#include <cmath>
#include <iostream>

using namespace std;

/* Parent class to all Geometric objects */
/* Passes to children normal Vector, Pigment value, and Finish value */
/* Passes to children virtual classes to Print values and Intersect object with Ray */
class Geometry {
public:
	Geometry();
	Geometry(Vector *n, Pigment *p, Finish *f);
	void SetNormal(Vector *normal);
	void SetPigment(Pigment *pigment);
	void SetFinish(Finish *finish);
	virtual void Print();
	virtual float Intersect(Ray *ray, Camera *camera);

	void setNormal(Vector *n);
	void setPigment(Pigment *p);
	void setFinish(Finish *f);

	Vector *getNormal();
	Pigment *getPigment();
	Finish *getFinish();

private:
	Vector normal;
	Pigment pigment;
	Finish finish;
};

#endif