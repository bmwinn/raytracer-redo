#include "Ray.h"

Ray::Ray() {
	start = Point();
	direction = Vector();
}

Ray::Ray(Point start, Vector direction) {
	this->start = start;
	this->direction = direction;
}

/* Constructor comes in handy during main pixel loop */
Ray::Ray(int i, int j, int width, int height, Camera *camera) {
	float us, vs, ws, right, left, bottom, top;
	this->start = Point(camera->center.x, camera->center.y, camera->center.z);
	
	right = camera->right.magnitude / 2.0;
	left = -1 * camera->right.magnitude / 2.0;
	bottom = -1 * camera->up.magnitude / 2.0;
	top = camera->up.magnitude / 2.0;

	us = left + (right - left) * (i + 0.5) / (float) width;
	vs = bottom + (top - bottom) * (j + 0.5) / (float) height;
	ws = -1;
	this->direction = Vector(us - camera->center.x, vs - camera->center.y, ws);
	this->direction.Normalize();
}