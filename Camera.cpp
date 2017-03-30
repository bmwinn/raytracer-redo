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
	cout << "  up         <" << up.x << ", " << up.y << ", " << up.z << ">" << endl;
	cout << "  right      <" << right.x << ", " << right.y << ", " << right.z << ">" << endl;
	cout << "  look_at    <" << lookat.getX() << ", " << lookat.getY() << ", " << lookat.getZ() << ">" << endl;
	cout << "}" << endl;
}