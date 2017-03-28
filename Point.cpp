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
	return sqrt(pow(x - other->x, 2) + pow(y - other->y, 2) + pow(z - other->z, 2));
}