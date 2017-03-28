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
	cout << "<" << normal.x << ", " << normal.y << ", " << normal.z << ">, " << distance << endl;
	cout << "  pigment {color <" << pigment.r << ", " << pigment.g << ", " << pigment.b << ", " << pigment.f << ">}" << endl;
	cout << "  finish {ambient " << finish.ambient << " diffuse " << finish.diffuse << "}" << endl;
	cout << "}" << endl;
}

 /* Return distance along ray to plane */
float Plane::Intersect(Ray *ray, Camera *camera) {
	float distance;
	Point onPlane = Point(this->distance * normal.x, this->distance * normal.y, this->distance * normal.z);
	Vector difCameraPlane = Vector(onPlane.x - camera->center.x, onPlane.y - camera->center.y, onPlane.z - camera->center.z);

	/* If dot product is 0, return no hit */
	if (ray->direction.Dot(&normal) == 0)
		distance = -1;
	else
		distance = difCameraPlane.Dot(&normal) / ray->direction.Dot(&normal);
	
	return distance;
}
