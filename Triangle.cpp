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
Triangle::Triangle(Point vA, Point vB, Point vC, Pigment pigment, Finish finish) : Geometry(pigment, finish) {
	vertexA = vA;
	vertexB = vB;
	vertexC = vC;
	setVectors();
}

void Triangle::setVectors() {
	AB = vertexA - vertexB;
	AC = vertexA - vertexC;
}
void Triangle::setVertexA(Point vA) { vertexA = vA; }
void Triangle::setVertexB(Point vB) { vertexB = vB; }
void Triangle::setVertexC(Point vC) { vertexC = vC; }
void Triangle::setAB(Vector ab) { AB = ab; }
void Triangle::setAC(Vector ac) { AC = ac; }

Point Triangle::getVertexA() { return vertexA; }
Point Triangle::getVertexB() { return vertexB; }
Point Triangle::getVertexC() { return vertexC; }
Vector Triangle::getAB() { return AB; }
Vector Triangle::getAC() { return AC; }
Vector Triangle::getNormal(Point surface, Ray ray) {
	Vector normal = AB.cross(AC);
	normal.normalize();

	if (ray.getDirection().dot(normal) > 0)
		normal *= -1;

	return normal;
}

void Triangle::print() {
	cout << "triangle {" << endl << "   ";
	vertexA.print();
	cout << "   ";
	vertexB.print();
	cout << "   ";
	vertexC.print();
	cout << "   ";
	pigment.print();
	cout << "   ";
	finish.print();
	cout << "}" << endl << endl;
}
void Triangle::printType() {
	cout << "Triangle" << endl;
}
float Triangle::intersect(int pw, int ph, Ray ray) {
	float distance, t, gamma, beta;
	float M, a, b, c, d, e, f, g, h, i, j, k, l;

	a = vertexA.x - vertexB.x;
	b = vertexA.y - vertexB.y;
	c = vertexA.z - vertexB.z;

	d = vertexA.x - vertexC.x;
	e = vertexA.y - vertexC.y;
	f = vertexA.z - vertexC.z;

	g = ray.getDirection().x;
	h = ray.getDirection().y;
	i = ray.getDirection().z;

	j = vertexA.x - ray.getStart().x;
	k = vertexA.y - ray.getStart().y;
	l = vertexA.z - ray.getStart().z;

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

Pigment Triangle::blinnPhong(int pw, int ph, Ray ray, float rayDistance, Point surface, Vector normal) {
	Pigment black = Pigment(0, 0, 0);
	Pigment pixel, ambient, diffuse;
	ambient = blinnPhongAmbient();

	bool noShadow = shadowFeeler(pw, ph, surface);
	
	if (noShadow) {
		diffuse = blinnPhongDiffuse(surface, normal);
	}
	else {
		diffuse = black;
	}

	pixel = ambient + diffuse;
	return pixel;
}