#include "Camera.h"

Camera::Camera() {
	center = Point();
	lookat = Point();
	up = Vector();
	right = Vector();
}

Camera::Camera(Point center, Vector up, Vector right, Point lookat) {
	this->center = center;
	this->up = up;
	this->right = right;
	this->lookat = lookat;
}

void Camera::Print() {
	cout << "camera {" << endl;
	cout << "  location   <" << center.getX() << ", " << center.getY() << ", " << center.getZ() << ">" << endl;
	cout << "  up         <" << up.getX() << ", " << up.getY() << ", " << up.getZ() << ">" << endl;
	cout << "  right      <" << right.getX() << ", " << right.getY() << ", " << right.getZ() << ">" << endl;
	cout << "  look_at    <" << lookat.getX() << ", " << lookat.getY() << ", " << lookat.getZ() << ">" << endl;
	cout << "}" << endl;
}

void Camera::setCenter(Point *c) {
	center.setX(c->getX());
	center.setY(c->getY());
	center.setZ(c->getZ());
}
void Camera::setLookAt(Point *l) {
	lookat.setX(l->getX());
	lookat.setY(l->getY());
	lookat.setZ(l->getZ());
}
void Camera::setUp(Vector *u) {
	up.setX(u->getX());
	up.setY(u->getY());
	up.setZ(u->getZ());
	up.setMagnitude(&up);
}
void Camera::setRight(Vector *r) {
	right.setX(r->getX());
	right.setY(r->getY());
	right.setZ(r->getZ());
	right.setMagnitude(&right);
}

Point *Camera::getCenter() { return &center; }
Point *Camera::getLookAt() { return &lookat; }
Vector *Camera::getUp() { return &up; }
Vector *Camera::getRight() { return &right; }
