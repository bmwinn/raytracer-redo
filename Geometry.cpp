#include "Geometry.h"

Geometry::Geometry() {
	normal = Vector();
	pigment = Pigment();
	finish = Finish();
	feeler = Ray();

	pigmentA = Pigment();
	pigmentD = Pigment();
	pigmentS = Pigment();
	pixel = Pigment();
	onGeom = Point();
}

Geometry::Geometry(Vector *n, Pigment *p, Finish *f) {
	normal = Vector();
	pigment = Pigment();
	finish = Finish();
	feeler = Ray();

	setNormal(n);
	setPigment(p);
	setFinish(f);

	pigmentA = Pigment();
	pigmentD = Pigment();
	pigmentS = Pigment();
	pixel = Pigment();
	onGeom = Point();	
}

/* Virtual function, should not be called */
void Geometry::print() {
	cout << "This is a Geometry object." << endl;
}
void Geometry::printType() {
	cout << "Geometry" << endl;
}

/* Virtual function, should not be called */
float Geometry::intersect(Ray *ray) {
	cout << "Geometry object intersect." << endl;
	return 10000;
}

void Geometry::setOnGeom(Ray *ray, float rayDistance) {
	onGeom.x = ray->getStart()->x + rayDistance * ray->getDirection()->x;
	onGeom.y = ray->getStart()->y + rayDistance * ray->getDirection()->y;
	onGeom.z = ray->getStart()->z + rayDistance * ray->getDirection()->z;
}

void Geometry::blinnPhong(Ray *ray, float rayDistance) { cout << "Geometry object Blinn Phong." << endl; }

void Geometry::blinnPhongAmbient() {
	Pigment cappedLight = Pigment(light->getPigment()->getR(), light->getPigment()->getG(), light->getPigment()->getB());
	if (cappedLight.getR() > 1)
		cappedLight.setR(1);

	if (cappedLight.getG() > 1)
		cappedLight.setG(1);

	if (cappedLight.getB() > 1)
		cappedLight.setB(1);

	pigmentA.setR(finish.getAmbient() * pigment.getR() * cappedLight.getR());
	pigmentA.setG(finish.getAmbient() * pigment.getG() * cappedLight.getG());
	pigmentA.setB(finish.getAmbient() * pigment.getB() * cappedLight.getB());

	pixel += &pigmentA;
}

void Geometry::blinnPhongDiffuse() {
	float zero = 0;

	Vector lightVector = *light->getCenter() - onGeom;
	lightVector.normalize();

	float dp = max(normal.dot(&lightVector), zero);
	pigmentD.setR(finish.getDiffuse() * pigment.getR() * light->getPigment()->getR() * dp);
	pigmentD.setG(finish.getDiffuse() * pigment.getG() * light->getPigment()->getG() * dp);
	pigmentD.setB(finish.getDiffuse() * pigment.getB() * light->getPigment()->getB() * dp);
	
	pixel += &pigmentD;
}

void Geometry::blinnPhongSpecular() {
	float zero = 0;

	Vector lightVector = *light->getCenter() - onGeom;
	Vector view = *camera->getCenter() - onGeom;
	lightVector.normalize();
	view.normalize();

	Vector half = view + lightVector;
	half.normalize();

	float shiny = 1.0/finish.getRoughness();
	float shine = pow(max(half.dot(&normal), zero), shiny);

	pigmentS.setR(finish.getSpecular() * pigment.getR() * light->getPigment()->getR() * shine);
	pigmentS.setG(finish.getSpecular() * pigment.getG() * light->getPigment()->getG() * shine);
	pigmentS.setB(finish.getSpecular() * pigment.getB() * light->getPigment()->getB() * shine);

	pixel += &pigmentS;
}

// Send shadow feeler ray from current geometry
// Return boolean that determines if another object blockes the light source from current object
// bool Geometry::shadowFeeler(Light *light, vector<Geometry *> *allGeometry) {
bool Geometry::shadowFeeler() {
	float dist = 0;
	float lightDistance = onGeom.distance(light->getCenter());

	Vector feelVector = *light->getCenter() - onGeom;
	feelVector.normalize();
	feeler = Ray(onGeom, feelVector);

	for (int geom = 0; geom < allGeometry->size(); geom++) {
		dist = allGeometry->at(geom)->intersect(&feeler);

		// if object with positive distance is closer than light source
		if (dist > 0.001 && dist < lightDistance)
			return false; // don't color pixel
	}

	return true;
}

void Geometry::setNormal(Vector *n) {
	normal = *n;
	normal.magnitude = n->magnitude;
}
void Geometry::setPigment(Pigment *p) {
	pigment.setR(p->getR());
	pigment.setG(p->getG());
	pigment.setB(p->getB());
	pigment.setF(p->getF());
}
void Geometry::setPigmentA(Pigment *pA) {
	pigmentA.setR(pA->getR());
	pigmentA.setG(pA->getG());
	pigmentA.setB(pA->getB());
	pigmentA.setF(pA->getF());
}
void Geometry::setPigmentD(Pigment *pD) {
	pigmentD.setR(pD->getR());
	pigmentD.setG(pD->getG());
	pigmentD.setB(pD->getB());
	pigmentD.setF(pD->getF());
}
void Geometry::setPigmentS(Pigment *pS) {
	pigmentS.setR(pS->getR());
	pigmentS.setG(pS->getG());
	pigmentS.setB(pS->getB());
	pigmentS.setF(pS->getF());
}

void Geometry::setFinish(Finish *f) {
	finish.setAmbient(f->getAmbient());
	finish.setDiffuse(f->getDiffuse());
	finish.setSpecular(f->getSpecular());
	finish.setRoughness(f->getRoughness());
}
void Geometry::setLight(Light *l) { light = l; }
void Geometry::setCamera(Camera *c) { camera = c; }
void Geometry::setAllGeometry(vector<Geometry *> *aG) { allGeometry = aG; }
void Geometry::setFeeler(Ray *f) { feeler = *f; }
void Geometry::setPixel(Pigment *p) { pixel = *p; }

Vector *Geometry::getNormal() { return &normal; }
Pigment *Geometry::getPigment() { return &pigment; }
Pigment *Geometry::getPigmentA() { return &pigmentA; }
Pigment *Geometry::getPigmentD() { return &pigmentD; }
Pigment *Geometry::getPigmentS() { return &pigmentS; }
Finish *Geometry::getFinish() { return &finish; }
Light *Geometry::getLight() { return light; }
Camera *Geometry::getCamera() { return camera; }
vector<Geometry *> *Geometry::getAllGeometry() { return allGeometry; }
Ray *Geometry::getFeeler() { return &feeler; }
Pigment *Geometry::getPixel() { return &pixel; }