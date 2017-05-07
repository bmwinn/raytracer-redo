#include "Sphere.h"

Sphere::Sphere() : Geometry() {
	center = Point();
	radius = 0;
}

Sphere::Sphere(Point center, float radius,
	Vector *normal, Pigment *pigment, Finish *finish) :
	Geometry(normal, pigment, finish) {
	this->center = center;
	this->radius = radius;
}

void Sphere::setCenter(Point *c) {
	center = *c;
	// center.setX(c->getX());
	// center.setY(c->getY());
	// center.setZ(c->getZ());
}
void Sphere::setRadius(float r) { radius = r; }

Point *Sphere::getCenter() { return &center; }
float Sphere::getRadius() { return radius; }

void Sphere::print() {
	cout << "sphere { ";
	cout << "<" << center.x << ", " << center.y << ", " << center.z << ">, " << radius << endl;
	cout << "  pigment { color <" << getPigment()->getR() << ", " << getPigment()->getG() << ", " << getPigment()->getB() << ", " << getPigment()->getF() << ">}" << endl;
	cout << "  finish {ambient " << getFinish()->getAmbient() << " diffuse " << getFinish()->getDiffuse() << "}" << endl;
	cout << "}" << endl;
}

 /* Return distance along ray to sphere */
float Sphere::intersect(Ray *ray, Point *point) {
	float distance, t1, t2, rad;
	Vector difPC = Vector(point->x - center.x, point->y - center.y, point->z - center.z);
	Vector difPCCopy = Vector(difPC.x, difPC.y, difPC.z);
	Vector dCopy = Vector(ray->getDirection()->x, ray->getDirection()->y, ray->getDirection()->z);

	rad = pow(ray->getDirection()->dot(&difPC), 2) - (ray->getDirection()->dot(&dCopy) * (difPC.dot(&difPCCopy)) - pow(radius, 2));

	/* If radicand is negative, return no hit */
	if (rad < 0)
		distance = -1;

	/* Return smallest (closest) positive distance */
	else if (rad == 0)
		distance = -1 * ray->getDirection()->dot(&difPC) / ray->getDirection()->dot(&dCopy);

	else {
		t1 = (-1 * ray->getDirection()->dot(&difPC) + sqrt(rad)) / ray->getDirection()->dot(&dCopy);
		t2 = (-1 * ray->getDirection()->dot(&difPC) - sqrt(rad)) / ray->getDirection()->dot(&dCopy);

		if (t1 > 0 && t2 > 0)
			distance = t1 < t2 ? t1 : t2;
		else if (t1 > 0 && t2 < 0)
			distance = t1;
		else if (t1 < 0 && t2 > 0)
			distance = t2;
		else if (t1 < 0 && t2 < 0)
			distance = -1;
	}

	return distance;
}

void Sphere::blinnPhong(Ray *ray, float rayDistance, Pigment *pixelPigment, Light *light, Camera *camera, 
	vector<Geometry *> *allGeometry) {
	setOnGeom(ray, rayDistance);
	Vector newNormal = Vector((onGeom.x - center.x)/radius,
					(onGeom.y - center.y)/radius,
					(onGeom.z - center.z)/radius);
	newNormal.normalize();
	setNormal(&newNormal);

	blinnPhongAmbient(pixelPigment, light);

	bool noShadow = shadowFeeler(light, allGeometry);
	if (noShadow) {
		blinnPhongDiffuse(pixelPigment, light);
		blinnPhongSpecular(pixelPigment, light, camera);
	}
}
