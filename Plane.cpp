#include "Plane.h"

Plane::Plane() : Geometry() {
	distance = 0;
}

Plane::Plane(float distance, Vector *normal, Pigment *pigment, Finish *finish) :
	Geometry(normal, pigment, finish) {
	this->distance = distance;
}

void Plane::setDistance(float d) { distance = d; }
// void Plane::setOnGeom() {
// 	onGeom.x = distance * normal.x;
// 	onGeom.y = distance * normal.y;
// 	onGeom.z = distance * normal.z;	
// }
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
float Plane::intersect(Ray *ray) {
	float distance;
	// Vector difPointPlane = onGeom - *ray->getStart();
	Point surface = Point(normal.x * distance, normal.y * distance, normal.z * distance);
	Vector difPointPlane = surface - *ray->getStart();
	// Vector difPointPlane = Vector(onGeom.x - ray->getStart()->x, onGeom.y - ray->getStart()->y, onGeom.z - ray->getStart()->z);

	/* If dot product is 0, return no hit */
	if (ray->getDirection()->dot(&normal) == 0)
		distance = -1;
	else
		distance = difPointPlane.dot(&normal) / ray->getDirection()->dot(&normal);
	
	return distance;
}

Pigment Plane::blinnPhong(Ray *ray, float rayDistance, Point surface) {
	// Geometry::setOnGeom(ray, rayDistance);
	Pigment black = Pigment(0, 0, 0);
	Pigment ambient, diffuse, pixel;

	ambient = blinnPhongAmbient();

	bool noShadow = shadowFeeler(surface);
	if (noShadow) {
		diffuse = blinnPhongDiffuse(surface);
	}
	else {
		diffuse = black;
	}

	pixel = ambient + diffuse;
	return pixel;
}
