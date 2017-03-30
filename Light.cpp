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
	cout << "color <" << pigment.r << ", " << pigment.g << ", " << pigment.b << ", " << pigment.f << ">}" << endl;
}