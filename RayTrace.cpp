#include "RayTrace.h"

void renderLoop(int width, int height, Image *img, vector<Geometry *> *allGeometry, Camera *camera, int bounces) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Ray *ray = new Ray(i, j, width, height, camera);
			Pigment fill = rayTrace(i, j, bounces, allGeometry, ray);
			colorPixel(i, j, img, &fill);
		}
	}
}

Pigment rayTrace(int pw, int ph, int bounces, vector<Geometry *> *allGeometry, Ray *ray) {
	int geomIndex;
	float closestDistance;
	Pigment black = Pigment(0, 0, 0);
	Point surface;
	Vector view;
	Geometry *hitGeom;

	if (bounces-- > 0) {
		geomIndex = geometryLoop(pw, ph, allGeometry, &closestDistance, ray);

		if (geomIndex == -1)
			return black;
		
		hitGeom = initialize(geomIndex, allGeometry, ray, closestDistance, &surface, &view);

		Pigment totalColor = findPigment(allGeometry, hitGeom, ray, pw, ph, view, closestDistance, surface, bounces);

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

Geometry *initialize(int index, vector<Geometry *> *aG, Ray *ray, float distance, Point *surface, Vector *view) {
	Geometry *curGeom = aG->at(index);
	*surface = findSurfacePoint(curGeom, ray, distance);
	*view = *curGeom->getCamera()->getCenter() - *surface;
	return curGeom;
}

Point findSurfacePoint(Geometry *curGeom, Ray *ray, float closestDistance) {
	Point surface = *ray->getStart();
	surface += *ray->getDirection() * closestDistance;
	return surface;
}

Pigment findPigment(vector<Geometry *> *aG, Geometry *hitGeom, Ray *ray, int pw, int ph, Vector view, float distance, Point surface, int bounces) {
	float fresnel, reflectionContribution, transmissionContribution, localContribution;
	Pigment localColor, reflectionColor, transmissionColor;

	setContributions(&fresnel, &reflectionContribution, &transmissionContribution, &localContribution, hitGeom, &view);
	localColor = hitGeom->blinnPhong(pw, ph, ray, distance, surface);

	reflectionColor = addReflectionColor(reflectionContribution, ray, pw, ph, bounces, aG, surface, hitGeom->getNormal());
	transmissionColor = addTransmissionColor(transmissionContribution, *ray->getDirection(), surface, *hitGeom->getNormal(), &view,
		hitGeom->getFinish()->ior, pw, ph, bounces, aG);

	Pigment totalColor = localColor * localContribution + reflectionColor * reflectionContribution + transmissionColor * transmissionContribution;

	return totalColor;
}

void setContributions(float *fresnel, float *reflCont, float *transCont, float *localCont, Geometry *curGeom, Vector *view) {
	Finish *finish = curGeom->getFinish();
	float filter = curGeom->getPigment()->f;

	*fresnel = schlicksApproximation(finish->ior, curGeom->getNormal(), view);

	*reflCont = (1 - filter) * finish->reflect + filter * *fresnel;
	*transCont = filter * (1 - *fresnel);
	*localCont = (1 - filter) * (1 - finish->reflect);
}

float schlicksApproximation(float ior, Vector *normal, Vector *view) {
	float F0 = pow(ior - 1, 2) / pow(ior + 1, 2);
	float schlicks = F0 + (1 - F0) * (1 - pow(normal->dot(view), 5));
	return schlicks;
}

Pigment addReflectionColor(float reflCont, Ray *ray, int pw, int ph, int bounces, vector<Geometry *> *aG, Point surface, Vector *normal) {
	Pigment reflColor;
	if (reflCont > 0) {
		Ray *reflRay = new Ray(ray, surface, normal);
		reflColor = rayTrace(pw, ph, bounces, aG, reflRay);
	}
	else {
		reflColor = Pigment(0, 0, 0);
	}

	return reflColor;
}

Pigment addTransmissionColor(float transCont, Vector initDir, Point surface, Vector normal, Vector *view, float ior,
	int pw, int ph, int bounces, vector<Geometry *> *aG) {
	Pigment transColor;

	if (transCont > 0) {
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
