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
}
void Sphere::setRadius(float r) { radius = r; }

Point *Sphere::getCenter() { return &center; }
float Sphere::getRadius() { return radius; }

void Sphere::print() {
	cout << "sphere { ";
	cout << "<" << center.x << ", " << center.y << ", " << center.z << ">, " << radius << endl;
	cout << "  pigment { color <" << pigment.r << ", " << pigment.g << ", " << pigment.b << ", " << pigment.f << ">}" << endl;
	cout << "  finish {ambient " << finish.ambient << " diffuse " << finish.diffuse << "}" << endl;
	cout << "}" << endl;
}
void Sphere::printType() {
	cout << "Sphere" << endl;
}

/* Return distance along ray to sphere */
float Sphere::intersect(int pw, int ph, Ray *ray) {
	float distance, t1, t2, rad;
	Vector difPC = *ray->getStart() - center;
	Vector rayD = *ray->getDirection();

	rad = pow(rayD.dot(&difPC), 2) - rayD.dot(&rayD) * ((difPC.dot(&difPC)) - pow(radius, 2));

	/* If radicand is negative, return no hit */
	if (rad < 0)
		distance = -1;

	/* Return smallest (closest) positive distance */
	else if (rad == 0)
		distance = -1 * rayD.dot(&difPC) / rayD.dot(&rayD);

	else {
		t1 = (-1 * rayD.dot(&difPC) + sqrt(rad)) / rayD.dot(&rayD);
		t2 = (-1 * rayD.dot(&difPC) - sqrt(rad)) / rayD.dot(&rayD);

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

Pigment Sphere::blinnPhong(int pw, int ph, Ray *ray, float rayDistance, Point surface) {
	Pigment pixel, ambient, diffuse, specular;
	Pigment black = Pigment(0, 0, 0);

	normal = surface - center;
	normal /= radius;
	normal.normalize();

	ambient = blinnPhongAmbient();

	bool noShadow = shadowFeeler(pw, ph, surface);
	if (noShadow) {
		diffuse = blinnPhongDiffuse(surface);
		specular = blinnPhongSpecular(surface);
	}
	else {
		diffuse = black;
		specular = black;
	}

	pixel = ambient + diffuse + specular;
	return pixel;
}
