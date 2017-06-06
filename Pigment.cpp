#include "Pigment.h"

/* Initialize Pigment to black */
Pigment::Pigment() {
	r = g = b = f = 0;
}

Pigment::Pigment(float r, float g, float b, float f) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->f = f;
	cap();
}

void Pigment::reset() {
	r = g = b = f = 0;
}

void Pigment::print() {
	cout << "pigment " << r << " " << g << " " << b << endl;
}

void Pigment::operator+=(Pigment other) {
	r += other.r;
	g += other.g;
	b += other.b;
	f += other.f;
	cap();
}
Pigment Pigment::operator*(float scalar) {
	Pigment result = Pigment(r * scalar, g * scalar, b * scalar, f);
	result.cap();
	return result;
}
Pigment Pigment::operator+(Pigment other) {
	Pigment result = Pigment(r + other.r, g + other.g, b + other.b, f);
	result.cap();
	return result;
}
void Pigment::cap() {
	if (r > 1) r = 1;
	if (g > 1) g = 1;
	if (b > 1) b = 1;
	if (f > 1) f = 1;

	if (r < 0) r = 0;
	if (g < 0) g = 0;
	if (b < 0) b = 0;
	if (f < 0) f = 0;
}