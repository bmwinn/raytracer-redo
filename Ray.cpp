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
Ray::Ray(int i, int j, int width, int height, Camera camera) {
	float us, vs, ws, right, left, bottom, top;
	start =  camera.getCenter();
	
	right = camera.getRight().magnitude / 2.0;
	left = -1 * camera.getRight().magnitude / 2.0;
	bottom = -1 * camera.getUp().magnitude / 2.0;
	top = camera.getUp().magnitude / 2.0;

	us = left + (right - left) * (i + 0.5) / (float) width;
	vs = bottom + (top - bottom) * (j + 0.5) / (float) height;
	ws = -1;

	/* Find, normalize new basis vectors */
	Vector w = camera.getCenter() - camera.getLookAt();
	w.normalize();

	Vector u = camera.getRight();
	u.normalize();

	Vector v = w.cross(u);
	// w.cross(&u, &v);

	/* Scale new basis vectors */
	u *= us;
	v *= vs;
	w *= ws;

	direction = u + v + w;
	direction.normalize();
}

Ray::Ray(Ray initial, Point surface, Vector normal) {
	start = surface;

	// d - 2 * ( d dot n) * n
	direction = initial.getDirection() - normal * ((float)2.0 * normal.dot(initial.getDirection()));
	direction.normalize();

	start += direction * 0.001;
}

// watch out for surface as your starting point
Ray::Ray(Point surface, Vector initialDirection, Vector *normal, Vector view, float ior1, float ior2) {
	start = surface;

	// check if exiting
	if (view.dot(*normal) <= 0) {
		// negate normal
		*normal *= -1;

		// swap iors
		// swap(ior1, ior2);
		float temp = ior1;
		ior1 = ior2;
		ior2 = temp;
	}

	float rad = 1 - (pow(ior1 / ior2, 2) * (1 - pow(initialDirection.dot(*normal), 2)));
	direction = (initialDirection - *normal * initialDirection.dot(*normal)) * (ior1 / ior2) - *normal * sqrt(rad);
	direction.normalize();

	start += direction * 0.001;
}

void Ray::setStart(Point s) { start = s; }
void Ray::setDirection(Vector d) { direction = d; }

Point Ray::getStart() { return start; }
Vector Ray::getDirection() { return direction; }

void Ray::print() {
	start.print();
	direction.print();
}
