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

/* Parent class to all Geometric objects */
/* Passes to children normal Vector, Pigment value, and Finish value */
/* Passes to children virtual classes to Print values and Intersect object with Ray */
class Geometry {
public:
	Geometry();
	Geometry(Pigment p, Finish f);

	virtual void print();
	virtual void printType();
	virtual float intersect(int pw, int ph, Ray ray);

	virtual Pigment blinnPhong(int pw, int ph, Ray ray, float rayDistance, Point surface, Vector normal);
	Pigment blinnPhongAmbient();
	Pigment blinnPhongDiffuse(Point surface, Vector normal);
	Pigment blinnPhongSpecular(Point surface, Vector normal);
	bool shadowFeeler(int pw, int ph, Point surface);

	void setPigment(Pigment p);
	void setFinish(Finish f);
	void setLight(Light l);
	void setCamera(Camera c);
	void setAllGeometry(vector<Geometry *> *aG);

	Pigment getPigment();
	Finish getFinish();
	Light getLight();
	Camera getCamera();
	vector<Geometry *> *getAllGeometry();
	virtual Vector getNormal(Point surface, Ray ray);

protected:
	Pigment pigment; // stores object color
	Finish finish;

	Light light;
	Camera camera;
	vector<Geometry *> *allGeometry; // vector list of all geometry objects, useful
};

#endif