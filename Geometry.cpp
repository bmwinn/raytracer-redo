#include "Geometry.h"

Geometry::Geometry() {
	normal = Vector();
	pigment = Pigment();
	finish = Finish();
	feeler = Ray();

	pigmentA = Pigment();
	pigmentD = Pigment();
	pigmentS = Pigment();
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
	onGeom = Point();	
}

/* Virtual function, should not be called */
void Geometry::print() {
	cout << "This is a Geometry object." << endl;
}

/* Virtual function, should not be called */
float Geometry::intersect(Ray *ray, Point *point) {
	cout << "Geometry object intersect." << endl;
	return 10000;
}

void Geometry::setOnGeom(Ray *ray, float rayDistance) {
	onGeom.setX(ray->getStart()->getX() + rayDistance * ray->getDirection()->getX());
	onGeom.setY(ray->getStart()->getY() + rayDistance * ray->getDirection()->getY());
	onGeom.setZ(ray->getStart()->getZ() + rayDistance * ray->getDirection()->getZ());
}

void Geometry::blinnPhong(Ray *ray, float rayDistance, Pigment *pixelPigment, Light *light, Camera *camera, vector<Geometry *> *allGeometry) {
	cout << "Geometry object Blinn Phong." << endl;
}

void Geometry::blinnPhongAmbient(Pigment *pixelPigment, Light *light) {
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

	*pixelPigment += &pigmentA;
}

void Geometry::blinnPhongDiffuse(Pigment *pixelPigment, Light *light) {
	float zero = 0;

	Vector lightVector = Vector(light->getCenter()->getX() - onGeom.getX(),
								light->getCenter()->getY() - onGeom.getY(),
								light->getCenter()->getZ() - onGeom.getZ());
	lightVector.normalize();

	float dp = max(normal.dot(&lightVector), zero);
	pigmentD.setR(finish.getDiffuse() * pigment.getR() * light->getPigment()->getR() * dp);
	pigmentD.setG(finish.getDiffuse() * pigment.getG() * light->getPigment()->getG() * dp);
	pigmentD.setB(finish.getDiffuse() * pigment.getB() * light->getPigment()->getB() * dp);
	
	*pixelPigment += &pigmentD;
}

void Geometry::blinnPhongSpecular(Pigment *pixelPigment, Light *light, Camera *camera) {
	float zero = 0;

	Vector lightVector = Vector(light->getCenter()->getX() - onGeom.getX(),
								light->getCenter()->getY() - onGeom.getY(),
								light->getCenter()->getZ() - onGeom.getZ());
	Vector view = Vector(camera->getCenter()->getX() - onGeom.getX(),
						 camera->getCenter()->getY() - onGeom.getY(),
						 camera->getCenter()->getZ() - onGeom.getZ());

	lightVector.normalize();
	view.normalize();

	Vector half = Vector(view.getX() + lightVector.getX(), view.getY() + lightVector.getY(), view.getZ() + lightVector.getZ());
	half.normalize();

	float shiny = 1.0/finish.getRoughness();
	float shine = pow(max(half.dot(&normal), zero), shiny);

	pigmentS.setR(finish.getSpecular() * pigment.getR() * light->getPigment()->getR() * shine);
	pigmentS.setG(finish.getSpecular() * pigment.getG() * light->getPigment()->getG() * shine);
	pigmentS.setB(finish.getSpecular() * pigment.getB() * light->getPigment()->getB() * shine);

	*pixelPigment += &pigmentS;
}

// Send shadow feeler ray from current geometry
// Return boolean that determines if another object blockes the light source from current object
bool Geometry::shadowFeeler(Light *light, vector<Geometry *> *allGeometry) {
	float dist = 0;
	float lightDistance = onGeom.distance(light->getCenter());

	Vector feelVector = Vector(light->getCenter()->getX() - onGeom.getX(),
								light->getCenter()->getY() - onGeom.getY(),
								light->getCenter()->getZ() - onGeom.getZ());
	feelVector.normalize();
	feeler = Ray(onGeom, feelVector);

	for (int geom = 0; geom < allGeometry->size(); geom++) {
		dist = allGeometry->at(geom)->intersect(&feeler, &onGeom);

		// if object with positive distance is closer than light source
		if (dist > 0.001 && dist < lightDistance)
			return false; // don't color pixel
	}

	return true;
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
