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
	void setPigmentA(Pigment *pA);
	void setPigmentD(Pigment *pD);
	void setPigmentS(Pigment *pS);
	void setFinish(Finish *f);
	void setLight(Light *l);
	void setCamera(Camera *c);
	void setAllGeometry(vector<Geometry *> *aG);
	void setFeeler(Ray *f);
	void setPixel(Pigment *p);

	Vector *getNormal();
	Point *getOnGeom();
	Pigment *getPigment();
	Pigment *getPigmentA();
	Pigment *getPigmentD();
	Pigment *getPigmentS();
	Finish *getFinish();
	Light *getLight();
	Camera *getCamera();
	vector<Geometry *> *getAllGeometry();
	Ray *getFeeler();
	Pigment *getPixel();

protected:
	Point onGeom; // stores point on geometry surface
	Vector normal;

	Pigment pigment; // stores object color
	Pigment pigmentA, pigmentD, pigmentS; // stores Ambient, Diffuse, Specular pigments during BP
	Finish finish;

	Light *light;
	Camera *camera;
	vector<Geometry *> *allGeometry;
	//Vector *view; add later
 
private:
	Ray feeler; // stores shadow feeler for Blinn Phong
	Pigment pixel;
};

#endif