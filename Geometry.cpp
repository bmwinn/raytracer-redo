#include "Geometry.h"

Geometry::Geometry() {
	normal = Vector();
	pigment = Pigment();
	finish = Finish();
}

void Geometry::SetNormal(Vector *other) {
	normal.setX(other->getX());
	normal.setY(other->getY());
	normal.setZ(other->getZ());
}

void Geometry::SetPigment(Pigment *other) {
	pigment.setR(other->getR());
	pigment.setG(other->getG());
	pigment.setB(other->getB());
	pigment.setF(other->getF());
}

void Geometry::SetFinish(Finish *other) {
	finish.setAmbient(other->getAmbient());
	finish.setDiffuse(other->getDiffuse());
	finish.setSpecular(other->getSpecular());
	finish.setRoughness(other->getRoughness());
}

/* Virtual function, should not be called */
void Geometry::Print() {
	cout << "This is a Geometry object." << endl;
}

/* Virtual function, should not be called */
float Geometry::Intersect(Ray *ray, Camera *camera) {
	cout << "Geometry object intersect." << endl;
	return 10000;
}

void Geometry::setNormal(Vector *n) {
	normal.setX(n->getX());
	normal.setY(n->getY());
	normal.setZ(n->getZ());
	normal.setMagnitude(n->getMagnitude());
}
void Geometry::setPigment(Pigment *p) {
	pigment.setR(p->getR());
	pigment.setG(p->getG());
	pigment.setB(p->getB());
	pigment.setF(p->getF());
}
void Geometry::setFinish(Finish *f) {
	finish.setAmbient(f->getAmbient());
	finish.setDiffuse(f->getDiffuse());
	finish.setSpecular(f->getSpecular());
	finish.setRoughness(f->getRoughness());
}

Vector *Geometry::getNormal() { return &normal; }
Pigment *Geometry::getPigment() { return &pigment; }
Finish *Geometry::getFinish() { return &finish; }
