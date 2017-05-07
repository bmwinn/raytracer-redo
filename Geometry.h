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
#include <string>

using namespace std;

// TODO: clean up publics and privates

/* Parent class to all Geometric objects */
/* Passes to children normal Vector, Pigment value, and Finish value */
/* Passes to children virtual classes to Print values and Intersect object with Ray */
class Geometry {
public:
	Geometry();
	Geometry(Vector *n, Pigment *p, Finish *f);
	virtual void print();
	virtual void printType();
	
	virtual float intersect(Ray *ray);
	
	void resetPigments();
	virtual void blinnPhong(Ray *ray, float rayDistance);
	void blinnPhongAmbient();
	void blinnPhongDiffuse();
	void blinnPhongSpecular();
	bool shadowFeeler();

	void setOnGeom(Ray *ray, float rayDistance);
	void setNormal(Vector *n);
	void setPigment(Pigment *p);
	void setFinish(Finish *f);

	Vector *getNormal();
	Pigment *getPigment();
	Finish *getFinish();

	Point onGeom; // stores point on geometry surface
	Pigment pigmentA, pigmentD, pigmentS; // stores Ambient, Diffuse, Specular pigments during BP

	Ray feeler; // stores shadow feeler for Blinn Phong
	Vector normal;

	Light *light;
	Camera *camera;
	vector<Geometry *> *allGeometry;
	Pigment *pixel;

private:
	Pigment pigment; // stores object color
	Finish finish;
};

#endif