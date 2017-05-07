#include "Plane.h"

Plane::Plane() : Geometry() {
	distance = 0;
}

Plane::Plane(float distance, Vector *normal, Pigment *pigment, Finish *finish) :
	Geometry(normal, pigment, finish) {
	this->distance = distance;
}

void Plane::setDistance(float d) { distance = d; }
void Plane::setOnGeom() {
	onGeom.x = distance * normal.x;
	onGeom.y = distance * normal.y;
	onGeom.z = distance * normal.z;	
}
float Plane::getDistance() { return distance; }


void Plane::print() {
	cout << "plane {";
	cout << "<" << getNormal()->x << ", " << getNormal()->y << ", " << getNormal()->z<< ">, " << distance << endl;
	cout << "  pigment {color <" << getPigment()->getR() << ", " << getPigment()->getG() << ", " << getPigment()->getB() << ", " << getPigment()->getF() << ">}" << endl;
	cout << "  finish {ambient " << getFinish()->getAmbient() << " diffuse " << getFinish()->getDiffuse() << "}" << endl;
	cout << "}" << endl;
}
void Plane::printType() { cout << "plane" << endl; }

 /* Return distance along ray to plane */
float Plane::intersect(Ray *ray) {
	float distance;
	Vector difPointPlane = onGeom - *ray->getStart();
	// Vector difPointPlane = Vector(onGeom.x - ray->getStart()->x, onGeom.y - ray->getStart()->y, onGeom.z - ray->getStart()->z);

	/* If dot product is 0, return no hit */
	if (ray->getDirection()->dot(getNormal()) == 0)
		distance = -1;
	else
		distance = difPointPlane.dot(getNormal()) / ray->getDirection()->dot(getNormal());
	
	return distance;
}

void Plane::blinnPhong(Ray *ray, float rayDistance, Pigment *pixelPigment, Light *light, Camera *camera, vector<Geometry *> *allGeometry) {
	Geometry::setOnGeom(ray, rayDistance);
	blinnPhongAmbient(pixelPigment, light);

	bool noShadow = shadowFeeler(light, allGeometry);
	if (noShadow) {
		blinnPhongDiffuse(pixelPigment, light);
	}
}
