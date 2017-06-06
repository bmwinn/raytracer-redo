#include "RayTrace.h"

void renderLoop(int width, int height, Image *img, vector<Geometry *> *allGeometry, Camera camera, int bounces) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Ray ray = Ray(i, j, width, height, camera);
			// if (i == PW and j == PH)
			// 	cout << "Iteration type: Primary" << endl;

			Pigment fill = rayTrace(i, j, bounces, allGeometry, ray);

			// if (i == PW and j == PH)
			// 	cout << "Pixel [" << i << ", " << j << "] Color: (" << fill.r << " " << fill.g << " " << fill.b << ")" << endl;
			
			colorPixel(i, j, img, fill);
		}
	}
}

Pigment rayTrace(int pw, int ph, int bounces, vector<Geometry *> *allGeometry, Ray ray) {
	Geometry *hitGeom;
	Vector view, normal;
	Point surface;
	int geomIndex;
	Pigment black = Pigment(0, 0, 0);
	float closestDistance = 10000;

	if (bounces-- > 0) {
		geomIndex = geometryLoop(pw, ph, allGeometry, &closestDistance, ray);
		if (geomIndex == -1)
			return black;

		view = initialize(hitGeom, &surface, &normal, geomIndex, allGeometry, ray, closestDistance);
		Pigment totalColor = findPigment(pw, ph, allGeometry, hitGeom, bounces, ray, view, closestDistance, surface, normal);
		return totalColor;
	}
	else {
		return black;
	}
}

float geometryLoop(int pw, int ph, vector<Geometry *> *allGeometry, float *closestDistance, Ray ray) {
	float distance;
	int geomIndex = -1;

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

Vector initialize(Geometry *&hitGeom, Point *surface, Vector *normal, int index, vector<Geometry *> *aG, Ray ray, float distance) {
	hitGeom = aG->at(index);

	*surface = findSurfacePoint(ray, distance);

	*normal = hitGeom->getNormal(*surface, ray);
	normal->normalize();
	
	Vector view = hitGeom->getCamera().getCenter() - *surface;
	view.normalize();
	return view;
}

Point findSurfacePoint(Ray ray, float closestDistance) {
	Point surface = ray.getStart();
	surface += ray.getDirection() * closestDistance;
	return surface;
}

Pigment findPigment(int pw, int ph, vector<Geometry *> *aG, Geometry *hitGeom, int bounces,
	Ray ray, Vector view, float distance, Point surface, Vector normal) {
	float fresnel, reflCont, transCont, localCont;
	Pigment localP, reflP, transP;
	float ior = hitGeom->getFinish().ior;

	setContributions(&fresnel, &reflCont, &transCont, &localCont, hitGeom, normal, view);
	localP = hitGeom->blinnPhong(pw, ph, ray, distance, surface, normal);

	reflP = addReflectionColor(pw, ph, aG, bounces, reflCont, ray, surface, normal);
	transP = addTransmissionColor(pw, ph, aG, bounces, transCont, ray.getDirection(), surface, normal, view, ior);

	Pigment totalColor = localP * localCont + reflP * reflCont + transP * transCont;

	return totalColor;
}

void setContributions(float *fresnel, float *reflCont, float *transCont, float *localCont, Geometry *hitGeom, Vector normal, Vector view) {
	Finish finish = hitGeom->getFinish();
	float filter = hitGeom->getPigment().f;

	// *fresnel = schlicksApproximation(finish.ior, normal, view);
	*fresnel = 0;

	*reflCont = (1 - filter) * finish.reflect + filter * *fresnel;
	*transCont = filter * (1 - *fresnel);
	*localCont = (1 - filter) * (1 - finish.reflect);
}

float schlicksApproximation(float ior, Vector normal, Vector view) {
	float F0 = pow(ior - 1, 2) / pow(ior + 1, 2);
	float dot = normal.dot(view);
	float schlicks = F0 + (1 - F0) * pow(1 - dot, 5);
	
	if (schlicks > 1 || schlicks < 0) {
		// cout << "  ior: " << ior << endl;
		cout << "  F0: " << F0 << endl;
		cout << "  dot: " << dot << endl;
		cout << "  schlicks: " << schlicks << endl;
	}

	return schlicks;
}

Pigment addReflectionColor(int pw, int ph, vector<Geometry *> *aG, int bounces, float reflCont, Ray ray, Point surface, Vector normal) {
	Pigment reflColor;

	if (reflCont > 0) {
		Ray reflRay = Ray(ray, surface, normal);
		// if (pw == PW and ph == PH)
		// 	cout << "Iteration type: Reflection" << endl;
		reflColor = rayTrace(pw, ph, bounces, aG, reflRay);
	}
	else {
		reflColor = Pigment(0, 0, 0);
	}

	return reflColor;
}

Pigment addTransmissionColor(int pw, int ph, vector<Geometry *> *aG, int bounces,
	float transCont, Vector initDir, Point surface, Vector normal, Vector view, float ior) {
	Pigment transColor;

	if (transCont > 0) {
		// if (pw == PW and ph == PH)
		// 	cout << "Iteration type: Refraction" << endl;
		Ray refrRay = Ray(surface, initDir, &normal, view, 1, ior);
		transColor = rayTrace(pw, ph, bounces, aG, refrRay);
	}
	else {
		transColor = Pigment(0, 0, 0);
	}

	return transColor;
}

void colorPixel(int pixelWidth, int pixelHeight, Image *img, Pigment pixel) {
	color_t color;
    setColor(&color, pixel);
    img->pixel(pixelWidth, pixelHeight, color);
}

/* Fill color_t variable (with Image.cpp compatibility) from my own Pigment class */
void setColor(color_t *color, Pigment pixelPigment) {
	color->r = pixelPigment.r * 255;
	color->g = pixelPigment.g * 255;
	color->b = pixelPigment.b * 255;
	color->f = pixelPigment.f;
}
