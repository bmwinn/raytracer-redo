#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Point.h"
#include "Vector.h"

#include <iostream>

using namespace std;

/* Contains Camera location "center", up Vector, right Vector, and lookat Point */
class Camera {
public:
	Camera();
	Camera(Point center, Vector up, Vector right, Point lookat);
	void print();

	void setCenter(Point *c);
	void setLookAt(Point *l);
	void setUp(Vector *u);
	void setRight(Vector *r);

	Point *getCenter();
	Point *getLookAt();
	Vector *getUp();
	Vector *getRight();

private:
	Point center, lookat;
	Vector up, right;
};

#endif