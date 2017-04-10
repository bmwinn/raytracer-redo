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
	cout << "<" << getNormal()->getX() << ", " << getNormal()->getY() << ", " << getNormal()->getZ() << ">, " << distance << endl;
	cout << "  pigment {color <" << getPigment()->getR() << ", " << getPigment()->getG() << ", " << getPigment()->getB() << ", " << getPigment()->getF() << ">}" << endl;
	cout << "  finish {ambient " << getFinish()->getAmbient() << " diffuse " << getFinish()->getDiffuse() << "}" << endl;
	cout << "}" << endl;
}

 /* Return distance along ray to plane */
float Plane::intersect(Ray *ray, Camera *camera) {
	float distance;
	Point onPlane = Point(this->distance * getNormal()->getX(), this->distance * getNormal()->getY(), this->distance * getNormal()->getZ());
	Vector difCameraPlane = Vector(onPlane.getX() - camera->getCenter()->getX(), onPlane.getY() - camera->getCenter()->getY(), onPlane.getZ() - camera->getCenter()->getZ());

	/* If dot product is 0, return no hit */
	if (ray->getDirection()->dot(getNormal()) == 0)
		distance = -1;
	else
		distance = difCameraPlane.dot(getNormal()) / ray->getDirection()->dot(getNormal());
	
	return distance;
}

void Plane::blinnPhong(int g, Ray *ray, float rayDistance, Pigment *pixelPigment, Light *light, Camera *camera, vector<Geometry *> *allGeometry) {
	Geometry::setOnGeom(ray, rayDistance);
	blinnPhongAmbient(pixelPigment, light);
	blinnPhongDiffuse(pixelPigment, light);
}
