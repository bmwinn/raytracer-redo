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
	start = Point(camera->getCenter()->getX(), camera->getCenter()->getY(), camera->getCenter()->getZ());
	
	right = camera->getRight()->getMagnitude() / 2.0;
	left = -1 * camera->getRight()->getMagnitude() / 2.0;
	bottom = -1 * camera->getUp()->getMagnitude() / 2.0;
	top = camera->getUp()->getMagnitude() / 2.0;

	us = left + (right - left) * (i + 0.5) / (float) width;
	vs = bottom + (top - bottom) * (j + 0.5) / (float) height;
	ws = -1;

	/* Find, normalize new basis vectors */
	Vector w = Vector(camera->getCenter()->getX() - camera->getLookAt()->getX(),
						camera->getCenter()->getY() - camera->getLookAt()->getY(),
						camera->getCenter()->getZ() - camera->getLookAt()->getZ());
	w.normalize();

	Vector u = Vector(camera->getRight()->getX(), camera->getRight()->getY(), camera->getRight()->getZ());
	u.normalize();

	Vector v = Vector();
	w.cross(&u, &v);

	/* Scale new basis vectors */
	u *= us;
	v *= vs;
	w *= ws;

	// this->direction = Vector(us - camera->getCenter()->getX(), vs - camera->getCenter()->getY(), ws);
	direction = Vector(u.getX() + v.getX() + w.getX(), u.getY() + v.getY() + w.getY(), u.getZ() + v.getZ() + w.getZ());
	direction.normalize();
}

void Ray::setStart(Point *s) {
	start.setX(s->getX());
	start.setY(s->getY());
	start.setZ(s->getZ());
}
void Ray::setDirection(Vector *d) {
	direction.setX(d->getX());
	direction.setY(d->getY());
	direction.setZ(d->getZ());
}

Point *Ray::getStart() { return &start; }
Vector *Ray::getDirection() { return &direction; }