#include "Plane.h"

Plane::Plane() : Geometry() {
	distance = 0;
}
Plane::Plane(float distance, Vector *normal, Pigment *pigment, Finish *finish) :
	Geometry(normal, pigment, finish) {
	this->distance = distance;
}

void Plane::setDistance(float d) { distance = d; }

float Plane::getDistance() { return distance; }

void Plane::print() {
	cout << "plane {";
	cout << "<" << normal.x << ", " << normal.y << ", " << normal.z<< ">, " << distance << endl;
	cout << "  pigment {color <" << pigment.r << ", " << pigment.g << ", " << pigment.b << ", " << pigment.f << ">}" << endl;
	cout << "  finish {ambient " << finish.ambient << " diffuse " << finish.diffuse << "}" << endl;
	cout << "}" << endl;
}
void Plane::printType() { cout << "plane" << endl; }

 /* Return distance along ray to plane */
// recompute point for shadows?
float Plane::intersect(int pw, int ph, Ray *ray) {
	float intersectDistance;
	Point surface = Point(normal.x * distance, normal.y * distance, normal.z * distance);
	Vector difPointPlane = surface - *ray->getStart();

	/* If dot product is 0, return no hit */
	if (ray->getDirection()->dot(&normal) == 0)
		intersectDistance = -1;
	else
		intersectDistance = difPointPlane.dot(&normal) / ray->getDirection()->dot(&normal);
	
	return intersectDistance;
}

Pigment Plane::blinnPhong(int pw, int ph, Ray *ray, float rayDistance, Point surface) {
	Pigment black = Pigment(0, 0, 0);
	Pigment ambient, diffuse, pixel;

	ambient = blinnPhongAmbient();

	bool noShadow = shadowFeeler(pw, ph, surface);
	if (noShadow) {
		diffuse = blinnPhongDiffuse(surface);
		return ambient + diffuse;
	}
	else {
		return ambient;
	}
}
