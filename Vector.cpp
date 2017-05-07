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
	result->setMagnitude(result->x, result->y, result->z);
}

void Vector::normalize() {
	if (magnitude <= 0) {
		cout << "bad magnitude" << endl;
		print();
	}

	else {
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
		magnitude = 1;
	}
}

void Vector::print() {
	cout << "Vector <" << x << ", " << y << ", " << z << ">" << endl;
}

void Vector::operator*=(float scalar) {
	x *= scalar;
	y *= scalar;
	z *= scalar;
	setMagnitude(x, y, z);
}
Vector Vector::operator-(Vector other) {
	return Vector(x - other.x, y - other.y, z - other.z);
}
Vector Vector::operator+(Vector other) {
	return Vector(x + other.x, y + other.y, z + other.z);
}

void Vector::setMagnitude(float x, float y, float z) {
	magnitude = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}
void Vector::setMagnitude(Vector *other) {
	magnitude = sqrt(pow(other->x, 2) + pow(other->y, 2) + pow(other->z, 2));
}
