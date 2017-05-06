// Point vertexA, vertexB, vertexC;
// Vector AB, BC;

#include "Triangle.h"

Triangle::Triangle() : Geometry() {
	vertexA = Point();
	vertexB = Point();
	vertexC = Point();
	AB = Vector();
	AC = Vector();
}
Triangle::Triangle(Point *vA, Point *vB, Point *vC) : Geometry() {
	// change to vertexA = *vA; ?
	vertexA = Point(vA->getX(), vA->getY(), vA->getZ());
	vertexB = Point(vB->getX(), vB->getY(), vB->getZ());
	vertexC = Point(vC->getX(), vC->getY(), vC->getZ());
	setVectors();

	normal = Vector();
	AB.cross(&AC, &normal);
	normal.normalize();
}

void Triangle::setVectors() {
	AB = Vector(vertexA.getX() - vertexB.getX(),
		        vertexA.getY() - vertexB.getY(),
		        vertexA.getZ() - vertexB.getZ());
	AC = Vector(vertexA.getX() - vertexC.getX(),
		        vertexA.getY() - vertexC.getY(),
		        vertexA.getZ() - vertexC.getZ());
}
void Triangle::setNormal(Ray *ray) {
	AB.cross(&AC, &normal);
	normal.normalize();

	if (ray->getDirection()->dot(&normal) > 0)
		normal *= -1;
}
void Triangle::print() {
	cout << "triangle {" << endl << "   ";
	vertexA.print();
	cout << "   ";
	vertexB.print();
	cout << "   ";
	vertexC.print();
	cout << "   ";
	getPigment()->print();
	cout << "   ";
	getFinish()->print();
	cout << "}" << endl << endl;
}
float Triangle::intersect(Ray *ray) {
	float distance, t, gamma, beta;
	float M, a, b, c, d, e, f, g, h, i, j, k, l;

	a = vertexA.getX() - vertexB.getX();
	b = vertexA.getY() - vertexB.getY();
	c = vertexA.getZ() - vertexB.getZ();

	d = vertexA.getX() - vertexC.getX();
	e = vertexA.getY() - vertexC.getY();
	f = vertexA.getZ() - vertexC.getZ();

	g = ray->getDirection()->getX();
	h = ray->getDirection()->getY();
	i = ray->getDirection()->getZ();

	j = vertexA.getX() - ray->getStart()->getX();
	k = vertexA.getY() - ray->getStart()->getY();
	l = vertexA.getZ() - ray->getStart()->getZ();

	M = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);
	t = -1 * (f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c))/M;

	if (t <= 0.001)
		return -1;

	gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c))/M;
	if (gamma >= 1 || gamma <= 0)
		return -1;

	beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g))/M;
	if (beta >= 1 || beta <= 0)
		return -1;

	if (beta > 0 && gamma > 0 && beta + gamma < 1)
		return t;
	else
		return -1;
}
// void Triangle::blinnPhong(Ray *ray, float rayDist) {
void Triangle::blinnPhong(Ray *ray, float rayDistance, Pigment *pixelPigment, Light *light,
	Camera *camera, vector<Geometry *> *allGeometry) {

	setOnGeom(ray, rayDistance);
	setNormal(ray);
	blinnPhongAmbient(pixelPigment, light);

	bool noShadow = shadowFeeler(light, allGeometry);

	if (noShadow) {
		blinnPhongDiffuse(pixelPigment, light);
	}
}