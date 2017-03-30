#include "Pigment.h"

/* Initialize Pigment to black */
Pigment::Pigment() {
	r = g = b = 0;
	f = 1;
}

Pigment::Pigment(float r, float g, float b, float f) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->f = f;
}

void Pigment::Reset() {
	r = g = b = 0;
	f = 1;
}