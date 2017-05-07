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

void Camera::print() {
	cout << "camera {" << endl;
	cout << "  location   <" << center.x << ", " << center.y << ", " << center.z << ">" << endl;
	cout << "  up         <" << up.x << ", " << up.y << ", " << up.z << ">" << endl;
	cout << "  right      <" << right.x << ", " << right.y << ", " << right.z << ">" << endl;
	cout << "  look_at    <" << lookat.x << ", " << lookat.y << ", " << lookat.z << ">" << endl;
	cout << "}" << endl;
}

void Camera::setCenter(Point *c) { center = *c; }
void Camera::setLookAt(Point *l) { lookat = *l; }
void Camera::setUp(Vector *u) {
	up = *u;
	up.magnitude = u->magnitude;
}
void Camera::setRight(Vector *r) {
	right = *r;
	right.magnitude = r->magnitude;
}

Point *Camera::getCenter() { return &center; }
Point *Camera::getLookAt() { return &lookat; }
Vector *Camera::getUp() { return &up; }
Vector *Camera::getRight() { return &right; }
