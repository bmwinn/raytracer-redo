#include "Geometry.h"

Geometry::Geometry() {
	normal = Vector();
	pigment = Pigment();
	finish = Finish();
}

Geometry::Geometry(Vector *n, Pigment *p, Finish *f) {
	normal = Vector();
	pigment = Pigment();
	finish = Finish();

	setNormal(n);
	setPigment(p);
	setFinish(f);
}

/* Virtual function, should not be called */
void Geometry::print() {
	cout << "This is a Geometry object." << endl;
}
void Geometry::printType() {
	cout << "Geometry" << endl;
}

/* Virtual function, should not be called */
float Geometry::intersect(int pw, int ph, Ray *ray) {
	cout << "Geometry object intersect." << endl;
	return 10000;
}

Pigment Geometry::blinnPhong(int pw, int ph, Ray *ray, float rayDistance, Point surface) {
	cout << "Geometry object Blinn Phong." << endl;
	return Pigment(0, 0, 0);
}

Pigment Geometry::blinnPhongAmbient() {
	Pigment cappedLight = *light->getPigment();
	if (cappedLight.g > 1)
		cappedLight.r = 1;

	if (cappedLight.g > 1)
		cappedLight.g = 1;

	if (cappedLight.b > 1)
		cappedLight.b = 1;

	Pigment ambient = Pigment(0, 0, 0);
	ambient.r = finish.ambient * pigment.r * cappedLight.r;
	ambient.g = finish.ambient * pigment.g * cappedLight.g;
	ambient.b = finish.ambient * pigment.b * cappedLight.b;

	return ambient;
}

Pigment Geometry::blinnPhongDiffuse(Point surface) {
	float zero = 0;

	Vector lightVector = *light->getCenter() - surface;
	lightVector.normalize();

	float dp = max(normal.dot(&lightVector), zero);

	Pigment diffuse = Pigment(0, 0, 0);
	diffuse.r = finish.diffuse * pigment.r * light->getPigment()->r * dp;
	diffuse.g = finish.diffuse * pigment.g * light->getPigment()->g * dp;
	diffuse.b = finish.diffuse * pigment.b * light->getPigment()->b * dp;
	
	return diffuse;
}

Pigment Geometry::blinnPhongSpecular(Point surface) {
	float zero = 0;

	Vector lightVector = *light->getCenter() - surface;
	Vector view = *camera->getCenter() - surface;
	lightVector.normalize();
	view.normalize();

	Vector half = view + lightVector;
	half.normalize();

	float shiny = 1.0 / finish.roughness;
	float shine = pow(max(half.dot(&normal), zero), shiny);

	Pigment specular = Pigment(0, 0, 0);
	specular.r = finish.specular * pigment.r * light->getPigment()->r * shine;
	specular.g = finish.specular * pigment.g * light->getPigment()->g * shine;
	specular.b = finish.specular * pigment.b * light->getPigment()->b * shine;

	return specular;
}

// Send shadow feeler ray from current geometry
// Return boolean that determines if another object blockes the light source from current object
// bool Geometry::shadowFeeler(Light *light, vector<Geometry *> *allGeometry) {
bool Geometry::shadowFeeler(int pw, int ph, Point surface) {
	float dist = 0;
	float lightDistance = surface.distance(light->getCenter());

	Vector feelVector = *light->getCenter() - surface;
	feelVector.normalize();
	surface += feelVector * 0.001;
	Ray feeler = Ray(surface, feelVector);

	for (int geom = 0; geom < allGeometry->size(); geom++) {
		dist = allGeometry->at(geom)->intersect(0, 0, &feeler);

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
void Geometry::setPigment(Pigment *p) { pigment = *p; }
void Geometry::setFinish(Finish *f) { finish = *f; }
void Geometry::setLight(Light *l) { light = l; }
void Geometry::setCamera(Camera *c) { camera = c; }
void Geometry::setAllGeometry(vector<Geometry *> *aG) { allGeometry = aG; }

Vector *Geometry::getNormal() { return &normal; }
Pigment *Geometry::getPigment() { return &pigment; }
Finish *Geometry::getFinish() { return &finish; }
Light *Geometry::getLight() { return light; }
Camera *Geometry::getCamera() { return camera; }
vector<Geometry *> *Geometry::getAllGeometry() { return allGeometry; }
