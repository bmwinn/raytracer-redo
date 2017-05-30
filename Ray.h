#ifndef _RAY_H_
#define _RAY_H_

#include "Point.h"
#include "Vector.h"
#include "Camera.h"

using namespace std;

class Ray {
public:
	Ray();
	Ray(Point start, Vector direction);
	Ray(int i, int j, int width, int height, Camera *camera);
	Ray(Ray *initial, Point surface, Vector *normal);
	Ray(Point surface, Vector initialDirection, Vector normal, Vector *view, float ior1, float ior2);
	void print();

	void setStart(Point *s);
	void setDirection(Vector *d);

	Point *getStart();
	Vector *getDirection();

private:
	Point start;
	Vector direction;
};

#endif