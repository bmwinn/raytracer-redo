#include "Light.h"

Light::Light() {
	center = Point();
	pigment = Pigment();
}

Light::Light(Point center, Pigment pigment) {
	this->center = center;
	this->pigment = pigment;
}

void Light::Print() {
	cout << "light {<" << center.x << ", " << center.y << ", " << center.z << "> ";
	cout << "color <" << pigment.r << ", " << pigment.g << ", " << pigment.b << ", " << pigment.f << ">}" << endl;
}

void Light::setCenter(Point *c) {
	center = *c;
}
void Light::setPigment(Pigment *p) {
	pigment.r = p->r;
	pigment.g = p->g;
	pigment.b = p->b;
	pigment.f = p->f;
}

Point *Light::getCenter() { return &center; }
Pigment *Light::getPigment() { return &pigment; }