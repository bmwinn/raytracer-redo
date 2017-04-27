#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "Vector.h"
#include "Pigment.h"
#include "Finish.h"
#include "Ray.h"
#include "Camera.h"
#include "Light.h"

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// TODO: clean up publics and privates

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
	virtual void print();
	virtual float intersect(Ray *ray, Point *point);
	
	virtual void blinnPhong(int g, Ray *ray, float rayDistance, Pigment *pixelPigment, Light *light, Camera *camera, vector<Geometry *> *allGeometry);
	void blinnPhongAmbient(Pigment *pixelPigment, Light *light);
	void blinnPhongDiffuse(Pigment *pixelPigment, Light *light);
	void blinnPhongSpecular(Pigment *pixelPigment, Light *light, Camera *camera);
	void setOnGeom(Ray *ray, float rayDistance);
	void resetPigments();

	bool shadowFeeler(int g, Light *light, vector<Geometry *> *allGeometry);

	void setNormal(Vector *n);
	void setPigment(Pigment *p);
	void setFinish(Finish *f);

	Vector *getNormal();
	Pigment *getPigment();
	Finish *getFinish();

	Point onGeom; // stores point on geometry surface
	Pigment pigmentA, pigmentD, pigmentS; // stores Ambient, Diffuse, Specular pigments during BP

	Ray feeler; // stores shadow feeler for Blinn Phong

private:
	Vector normal;
	Pigment pigment; // stores object color
	Finish finish;
};

#endif