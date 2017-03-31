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
	cout << "light {<" << center.getX() << ", " << center.getY() << ", " << center.getZ() << "> ";
	cout << "color <" << pigment.getR() << ", " << pigment.getG() << ", " << pigment.getB() << ", " << pigment.getF() << ">}" << endl;
}

void Light::setCenter(Point *c) {
	center.setX(c->getX());
	center.setY(c->getY());
	center.setZ(c->getZ());
}
void Light::setPigment(Pigment *p) {
	pigment.setR(p->getR());
	pigment.setG(p->getG());
	pigment.setB(p->getB());
	pigment.setF(p->getF());
}

Point *Light::getCenter() { return &center; }
Pigment *Light::getPigment() { return &pigment; }