#include "RayTrace.h"

void renderLoop(int width, int height, Image *img, vector<Geometry *> *allGeometry, Camera *camera, int bounces) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Ray ray = Ray(i, j, width, height, camera);
			// if (i == PW and j == PH)
			// 	cout << "Iteration type: Primary" << endl;

			Pigment fill = rayTrace(i, j, bounces, allGeometry, ray);

			// if (i == PW and j == PH)
			// 	cout << "Pixel [" << i << ", " << j << "] Color: (" << fill.r << " " << fill.g << " " << fill.b << ")" << endl;
			
			colorPixel(i, j, img, &fill);
		}
	}
}

Pigment rayTrace(int pw, int ph, int bounces, vector<Geometry *> *allGeometry, Ray ray) {
	int geomIndex;
	float closestDistance;
	Pigment black = Pigment(0, 0, 0);
	Point surface;
	Vector view;
	Vector normal;
	Geometry *hitGeom;

	if (bounces-- > 0) {
		geomIndex = geometryLoop(pw, ph, allGeometry, &closestDistance, ray);

		if (geomIndex == -1)
			return black;

		hitGeom = initialize(geomIndex, allGeometry, ray, closestDistance, &surface, &view, &normal);

		if (pw == PW and ph == PH)
			normal->print();

		Pigment totalColor = findPigment(allGeometry, hitGeom, ray, pw, ph, view, closestDistance, surface, normal, bounces);

		return totalColor;
	}
	else {
		return black;
	}
}

float geometryLoop(int pw, int ph, vector<Geometry *> *allGeometry, float *closestDistance, Ray *ray) {
	float distance;
	int geomIndex = -1;
	*closestDistance = 10000;

	for (int i = 0; i < allGeometry->size(); i++) {
		Geometry *curGeom = allGeometry->at(i);
		distance = curGeom->intersect(pw, ph, ray);
		if (distance > 0.0001 && distance < *closestDistance) {
			*closestDistance = distance;
			geomIndex = i;
		}
	}

	return geomIndex;
}

Geometry *initialize(int index, vector<Geometry *> *aG, Ray *ray, float distance, Point *surface, Vector *view, Vector *normal) {
	Geometry *hitGeom = aG->at(index);

	*surface = findSurfacePoint(ray, distance);

	normal = hitGeom->getNormal(*surface, *ray);
	normal->print();
	normal->normalize();
	
	view = *hitGeom->getCamera()->getCenter() - *surface;
	view->normalize();
	
	return hitGeom;
}

Point findSurfacePoint(Ray *ray, float closestDistance) {
	Point surface = *ray->getStart();
	surface += *ray->getDirection() * closestDistance;
	return surface;
}

Pigment findPigment(vector<Geometry *> *aG, Geometry *hitGeom, Ray *ray, int pw, int ph, Vector *view, float distance, Point surface, Vector *normal, 
	int bounces) {
	float fresnel, reflCont, transCont, localCont;
	Pigment localP, reflP, transP;
	// Vector *normal = hitGeom->getNormal();
	float ior = hitGeom->getFinish()->ior;

	setContributions(&fresnel, &reflCont, &transCont, &localCont, hitGeom, normal, view);
	localP = hitGeom->blinnPhong(pw, ph, ray, distance, surface, *normal);

	reflP = addReflectionColor(reflCont, ray, pw, ph, bounces, aG, surface, normal);
	transP = addTransmissionColor(transCont, *ray->getDirection(), surface, normal, view, ior, pw, ph, bounces, aG);

	Pigment totalColor = localP * localCont + reflP * reflCont + transP * transCont;

	return totalColor;
}

void setContributions(float *fresnel, float *reflCont, float *transCont, float *localCont, Geometry *hitGeom, Vector *normal, Vector *view) {
	Finish *finish = hitGeom->getFinish();
	float filter = hitGeom->getPigment()->f;

	// *fresnel = schlicksApproximation(finish->ior, normal, view);
	// *fresnel = 0;

	*reflCont = (1 - filter) * finish->reflect + filter * *fresnel;
	*transCont = filter * (1 - *fresnel);
	*localCont = (1 - filter) * (1 - finish->reflect);
}

float schlicksApproximation(float ior, Vector *normal, Vector *view) {
	float F0 = pow(ior - 1, 2) / pow(ior + 1, 2);
	float dot = normal->dot(view);
	float schlicks = F0 + (1 - F0) * pow(1 - dot, 5);
	
	if (schlicks > 1 || schlicks < 0) {
		// cout << "  ior: " << ior << endl;
		cout << "  F0: " << F0 << endl;
		cout << "  dot: " << dot << endl;
		cout << "  schlicks: " << schlicks << endl;
	}

	return schlicks;
}

Pigment addReflectionColor(float reflCont, Ray *ray, int pw, int ph, int bounces, vector<Geometry *> *aG, Point surface, Vector *normal) {
	Pigment reflColor;

	if (reflCont > 0) {
		Ray *reflRay = new Ray(ray, surface, normal);
		// if (pw == PW and ph == PH)
		// 	cout << "Iteration type: Reflection" << endl;
		reflColor = rayTrace(pw, ph, bounces, aG, reflRay);
	}
	else {
		reflColor = Pigment(0, 0, 0);
	}

	return reflColor;
}

Pigment addTransmissionColor(float transCont, Vector initDir, Point surface, Vector *normal, Vector *view, float ior,
	int pw, int ph, int bounces, vector<Geometry *> *aG) {
	Pigment transColor;

	if (transCont > 0) {
		// if (pw == PW and ph == PH)
		// 	cout << "Iteration type: Refraction" << endl;
		Ray *refrRay = new Ray(surface, initDir, normal, view, 1, ior);
		transColor = rayTrace(pw, ph, bounces, aG, refrRay);
	}
	else {
		transColor = Pigment(0, 0, 0);
	}

	return transColor;
}

/* Fill color_t variable (with Image.cpp compatibility) from my own Pigment class */
void setColor(color_t *color, Pigment *pixelPigment) {
	color->r = pixelPigment->r * 255;
	color->g = pixelPigment->g * 255;
	color->b = pixelPigment->b * 255;
	color->f = pixelPigment->f;
}

void colorPixel(int pixelWidth, int pixelHeight, Image *img, Pigment *pixel) {
	color_t color;
    setColor(&color, pixel);
    img->pixel(pixelWidth, pixelHeight, color);
}
