#include "Plane.h"

Plane::Plane() : Geometry() {
	norm = Vector(0, 1, 0);
	distance = 0;
}
Plane::Plane(float distance, Vector normal, Pigment pigment, Finish finish) :
	Geometry(pigment, finish) {
	norm = normal;
	this->distance = distance;
}

void Plane::setDistance(float d) { distance = d; }
void Plane::setNorm(Vector n) {
	norm = n;
	norm.setMagnitude(n);
	norm.normalize();
}

float Plane::getDistance() { return distance; }
Vector Plane::getNormal(Point surface, Ray ray) { return norm; }
Vector Plane::getNorm() { return norm; }

void Plane::print() {
	cout << "plane {";
	cout << "<" << norm.x << ", " << norm.y << ", " << norm.z<< ">, " << distance << endl;
	pigment.print();
	finish.print();
}
void Plane::printType() { cout << "plane" << endl; }

 /* Return distance along ray to plane */
float Plane::intersect(int pw, int ph, Ray ray) {
	float intersectDistance;
	Point surface = Point(norm.x * distance, norm.y * distance, norm.z * distance);
	Vector difPointPlane = surface - ray.getStart();

	/* If dot product is 0, return no hit */
	if (ray.getDirection().dot(norm) == 0)
		intersectDistance = -1;
	else
		intersectDistance = difPointPlane.dot(norm) / ray.getDirection().dot(norm);
	
	return intersectDistance;
}

Pigment Plane::blinnPhong(int pw, int ph, Ray ray, float rayDistance, Point surface, Vector normal) {
	Pigment black = Pigment(0, 0, 0);
	Pigment ambient, diffuse, pixel;

	ambient = blinnPhongAmbient();

	bool noShadow = shadowFeeler(pw, ph, surface);
	if (noShadow) {
		diffuse = blinnPhongDiffuse(surface, normal);
		return ambient + diffuse;
	}
	else {
		return ambient;
	}
}
