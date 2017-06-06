#include "Light.h"

Light::Light() {
	center = Point();
	pigment = Pigment();
}

Light::Light(Point center, Pigment pigment) {
	this->center = center;
	this->pigment = pigment;
}

void Light::print() {
	cout << "light {";
	center.print();
	cout << "color <";
	pigment.print();
}

void Light::setCenter(Point c) { center = c; }
void Light::setPigment(Pigment p) { pigment = p; }

Point Light::getCenter() { return center; }
Pigment Light::getPigment() { return pigment; }