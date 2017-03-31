#include "Plane.h"

Plane::Plane() {
	normal = Vector();
	distance = 0;
	pigment = Pigment();
	finish = Finish();
}

Plane::Plane(Vector normal, float distance, Pigment pigment, Finish finish) {
	this->normal = normal;
	this->distance = distance;
	this->pigment = pigment;
	this->finish = finish;
}

void Plane::Print() {
	cout << "plane {";
	cout << "<" << normal.getX() << ", " << normal.getY() << ", " << normal.getZ() << ">, " << distance << endl;
	cout << "  pigment {color <" << pigment.getR() << ", " << pigment.getG() << ", " << pigment.getB() << ", " << pigment.getF() << ">}" << endl;
	cout << "  finish {ambient " << finish.getAmbient() << " diffuse " << finish.getDiffuse() << "}" << endl;
	cout << "}" << endl;
}

 /* Return distance along ray to plane */
float Plane::Intersect(Ray *ray, Camera *camera) {
	float distance;
	Point onPlane = Point(this->distance * normal.getX(), this->distance * normal.getY(), this->distance * normal.getZ());
	Vector difCameraPlane = Vector(onPlane.getX() - camera->getCenter()->getX(), onPlane.getY() - camera->getCenter()->getY(), onPlane.getZ() - camera->getCenter()->getZ());

	/* If dot product is 0, return no hit */
	if (ray->getDirection()->dot(&normal) == 0)
		distance = -1;
	else
		distance = difCameraPlane.dot(&normal) / ray->getDirection()->dot(&normal);
	
	return distance;
}
