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
	void Print();
	Point center, lookat;
	Vector up, right;
};

#endif