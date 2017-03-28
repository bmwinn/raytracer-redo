#include "Vector.h"
#include <cmath>

Vector::Vector() {
	x = y = z = 0;
}

Vector::Vector(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	magnitude = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void Vector::SetMagnitude(float x, float y, float z) {
	magnitude = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

float Vector::Dot(Vector *other) {
	return x * other->x + y * other->y + z * other->z;
}

void Vector::Cross(Vector *other, Vector *result) {
	result->x = y * other->z - z * other->y;
	result->y = -1 * (x * other->z - z * other->x);
	result->z = x * other->y - y * other->x;
}

void Vector::Normalize() {
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
	magnitude = 1;
}
