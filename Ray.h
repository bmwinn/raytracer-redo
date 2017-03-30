#ifndef _RAY_H_
#define _RAY_H_

#include "Point.h"
#include "Vector.h"
#include "Camera.h"

class Ray {
public:
	Ray();
	Ray(Point start, Vector direction);
	Ray(int i, int j, int width, int height, Camera *camera);
	Point start;
	Vector direction;
};

#endif