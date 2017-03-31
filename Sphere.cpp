#include "Sphere.h"

// Sphere::Sphere() : Geometry() {}
Sphere::Sphere() : Geometry() {
	center = Point();
	radius = 0;
	// normal = Vector();
	// pigment = Pigment();
	// finish = Finish();
}

// Sphere::Sphere() : Geometry(...) {}
Sphere::Sphere(Point center, float radius, Pigment pigment, Finish finish) {
	this->center = center;
	this->radius = radius;
	setPigment(&pigment);
	setFinish(&finish);
}

void Sphere::Print() {
	cout << "sphere { ";
	cout << "<" << center.getX() << ", " << center.getY() << ", " << center.getZ() << ">, " << radius << endl;
	cout << "  pigment { color <" << getPigment()->getR() << ", " << getPigment()->getG() << ", " << getPigment()->getB() << ", " << getPigment()->getF() << ">}" << endl;
	cout << "  finish {ambient " << getFinish()->getAmbient() << " diffuse " << getFinish()->getDiffuse() << "}" << endl;
	cout << "}" << endl;
}

 /* Return distance along ray to sphere */
float Sphere::Intersect(Ray *ray, Camera *camera) {
	float distance, t1, t2, rad;
	Vector difPC = Vector(camera->getCenter()->getX() - center.getX(), camera->getCenter()->getY() - center.getY(), camera->getCenter()->getZ() - center.getZ());
	Vector difPCCopy = Vector(difPC.getX(), difPC.getY(), difPC.getZ());
	Vector dCopy = Vector(ray->getDirection()->getX(), ray->getDirection()->getY(), ray->getDirection()->getZ());

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
