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
	start = *camera->getCenter();
	
	right = camera->getRight()->magnitude / 2.0;
	left = -1 * camera->getRight()->magnitude / 2.0;
	bottom = -1 * camera->getUp()->magnitude / 2.0;
	top = camera->getUp()->magnitude / 2.0;

	us = left + (right - left) * (i + 0.5) / (float) width;
	vs = bottom + (top - bottom) * (j + 0.5) / (float) height;
	ws = -1;

	/* Find, normalize new basis vectors */
	Vector w = *camera->getCenter() - *camera->getLookAt();
	w.normalize();

	Vector u = *camera->getRight();
	u.normalize();

	Vector v = Vector();
	w.cross(&u, &v);

	/* Scale new basis vectors */
	u *= us;
	v *= vs;
	w *= ws;

	direction = u + v + w;
	direction.normalize();
}

void Ray::print() {
	start.print();
	direction.print();
}

void Ray::setStart(Point *s) {
	start = *s;
}
void Ray::setDirection(Vector *d) {
	direction = *d;
}

Point *Ray::getStart() { return &start; }
Vector *Ray::getDirection() { return &direction; }