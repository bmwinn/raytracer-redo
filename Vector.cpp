#include "Vector.h"

Vector::Vector() {
	x = y = z = 0;
}

Vector::Vector(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	magnitude = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

float Vector::dot(Vector *other) {
	return x * other->x + y * other->y + z * other->z;
}

void Vector::cross(Vector *other, Vector *result) {
	result->x = y * other->z - z * other->y;
	result->y = -1 * (x * other->z - z * other->x);
	result->z = x * other->y - y * other->x;
}

void Vector::normalize() {
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
	magnitude = 1;
}

void Vector::setX(float x) { this->x = x; }
void Vector::setY(float y) { this->y = y; }
void Vector::setZ(float z) { this->z = z; }
void Vector::setMagnitude(float x, float y, float z) {
	magnitude = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

float Vector::getX() { return x; }
float Vector::getY() { return y; }
float Vector::getZ() { return z; }
float Vector::getMagnitude() { return magnitude; }