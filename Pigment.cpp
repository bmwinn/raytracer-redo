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

void Pigment::setR(float r) { this->r = r; }
void Pigment::setG(float g) { this->g = g; }
void Pigment::setB(float b) { this->b = b; }
void Pigment::setF(float f) { this->f = f; }

float Pigment::getR() { return r; }
float Pigment::getG() { return g; }
float Pigment::getB() { return b; }
float Pigment::getF() { return f; }