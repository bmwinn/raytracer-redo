#include "Point.h"
#include <cmath>

Point::Point() {
	x = y = z = 0;
}

Point::Point(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Point::~Point() {}

float Point::distance(Point *other) {
	return sqrt(pow(x - other->getX(), 2) + pow(y - other->getY(), 2) + pow(z - other->getZ(), 2));
}

void Point::setX(float x) { this->x = x; }
void Point::setY(float y) { this->y = y; }
void Point::setZ(float z) { this->z = z; }

float Point::getX() { return x; }
float Point::getY() { return y; }
float Point::getZ() { return z; }
