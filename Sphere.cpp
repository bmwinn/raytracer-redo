#include "Sphere.h"

Sphere::Sphere() {
	center = Point();
	radius = 0;
	normal = Vector();
	pigment = Pigment();
	finish = Finish();
}

Sphere::Sphere(Point center, float radius, Pigment pigment, Finish finish) {
	this->center = center;
	this->radius = radius;
	this->pigment = pigment;
	this->finish = finish;
}

void Sphere::Print() {
	cout << "sphere { ";
	cout << "<" << center.getX() << ", " << center.getY() << ", " << center.getZ() << ">, " << radius << endl;
	cout << "  pigment { color <" << pigment.r << ", " << pigment.g << ", " << pigment.b << ", " << pigment.f << ">}" << endl;
	cout << "  finish {ambient " << finish.ambient << " diffuse " << finish.diffuse << "}" << endl;
	cout << "}" << endl;
}

 /* Return distance along ray to sphere */
float Sphere::Intersect(Ray *ray, Camera *camera) {
	float distance, t1, t2, rad;
	Vector difPC = Vector(camera->center.getX() - center.getX(), camera->center.getY() - center.getY(), camera->center.getZ() - center.getZ());
	Vector difPCCopy = Vector(difPC.getX(), difPC.getY(), difPC.getZ());
	Vector dCopy = Vector(ray->direction.getX(), ray->direction.getY(), ray->direction.getZ());

	rad = pow(ray->direction.dot(&difPC), 2) - (ray->direction.dot(&dCopy) * (difPC.dot(&difPCCopy)) - pow(radius, 2));

	/* If radicand is negative, return no hit */
	if (rad < 0)
		distance = -1;

	/* Return smallest (closest) positive distance */
	else if (rad == 0)
		distance = -1 * ray->direction.dot(&difPC) / ray->direction.dot(&dCopy);

	else {
		t1 = (-1 * ray->direction.dot(&difPC) + sqrt(rad)) / ray->direction.dot(&dCopy);
		t2 = (-1 * ray->direction.dot(&difPC) - sqrt(rad)) / ray->direction.dot(&dCopy);

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
