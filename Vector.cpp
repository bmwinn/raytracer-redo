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

float Vector::dot(Vector other) {
	return x * other.x + y * other.y + z * other.z;
}

Vector Vector::cross(Vector other) {
	Vector result = Vector( y * other.z - z * other.y,
						   -1 * (x * other.z - z * other.x),
						    x * other.y - y * other.x);
	return result;
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
void Vector::operator/=(float scalar) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
	setMagnitude(x, y, z);
}
void Vector::operator-=(Vector other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	setMagnitude(x, y, z);
}
Vector Vector::operator-(Vector other) {
	return Vector(x - other.x, y - other.y, z - other.z);
}
Vector Vector::operator+(Vector other) {
	return Vector(x + other.x, y + other.y, z + other.z);
}
Vector Vector::operator*(float scalar) {
	return Vector(x * scalar, y * scalar, z * scalar);
}

void Vector::setMagnitude(float x, float y, float z) {
	magnitude = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}
void Vector::setMagnitude(Vector other) {
	magnitude = sqrt(pow(other.x, 2) + pow(other.y, 2) + pow(other.z, 2));
}
