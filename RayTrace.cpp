#include "RayTrace.h"

void debugPixel(int i, int j, Pigment fill) {
	if (i == PW and j == PH) {
		cout << "Iteration type: Primary" << endl;
		cout << "Pixel [" << i << ", " << j << "] Color: (" << fill.r << " " << fill.g << " " << fill.b << ")" << endl;
	}
}

// send a ray to each pixel in the result image
void renderLoop(int width, int height, Image *img, vector<Geometry *> *allGeometry, Camera camera, int bounces) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {

			// create a ray from the camera towards pixel
			Ray ray = Ray(i, j, width, height, camera);
			
			// find the color at this pixel location by ray tracing
			Pigment fill = rayTrace(i, j, bounces, allGeometry, ray);

			// fill in this pixel with the color found
			colorPixel(i, j, img, fill);

			debugPixel(i, j, fill);
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

	// Check recursion
	// If we have bounced too many times
	// Return black
	if (bounces-- > 0) {

		// Did this ray hit anything?
		geomIndex = geometryLoop(pw, ph, allGeometry, &closestDistance, ray);

		// If this ray didn't hit anything
		// Return black
		if (geomIndex == -1)
			return black;

		// We hit an object!
		// Initialize view vector, surface point, normal vector
		view = initialize(hitGeom, &surface, &normal, geomIndex, allGeometry, ray, closestDistance);

		// Find the color of what we hit
		Pigment totalColor = findPigment(pw, ph, allGeometry, hitGeom, bounces, ray, view, closestDistance, surface, normal);
		return totalColor;
	}
	else {
		return black;
	}
}

// Find the closest geometry object
// Return its index
float geometryLoop(int pw, int ph, vector<Geometry *> *allGeometry, float *closestDistance, Ray ray) {
	float distance;
	int geomIndex = -1;

	for (int i = 0; i < allGeometry->size(); i++) {
		Geometry *curGeom = allGeometry->at(i);

		// Send a ray towards this object
		distance = curGeom->intersect(pw, ph, ray);

		// Find the closest object
		if (distance > 0.0001 && distance < *closestDistance) {
			*closestDistance = distance;
			geomIndex = i;
		}
	}

	return geomIndex;
}

// Init surface point, normal, view vector
Vector initialize(Geometry *&hitGeom, Point *surface, Vector *normal, int index, vector<Geometry *> *aG, Ray ray, float distance) {
	// Keep track of which geometry object was intersected
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

// Pigment at one pixel comes from local, reflected, AND refracted colors
Pigment findPigment(int pw, int ph, vector<Geometry *> *aG, Geometry *hitGeom, int bounces,
	Ray ray, Vector view, float distance, Point surface, Vector normal) {
	float fresnel, reflCont, transCont, localCont;
	Pigment localP, reflP, transP;
	float ior = hitGeom->getFinish().ior;

	// Initialize many constants
	setContributions(&fresnel, &reflCont, &transCont, &localCont, hitGeom, normal, view);
	
	// Find local color thru BRDF :D
	localP = hitGeom->blinnPhong(pw, ph, ray, distance, surface, normal);

	// Find reflected and refracted colors
	reflP = addReflectionColor(pw, ph, aG, bounces, reflCont, ray, surface, normal);
	transP = addTransmissionColor(pw, ph, aG, bounces, transCont, ray.getDirection(), surface, normal, view, ior);

	// Add contributions
	Pigment totalColor = localP * localCont + reflP * reflCont + transP * transCont;

	return totalColor;
}

void setContributions(float *fresnel, float *reflCont, float *transCont, float *localCont, Geometry *hitGeom, Vector normal, Vector view) {
	Finish finish = hitGeom->getFinish();
	float filter = hitGeom->getPigment().f;

	// Eventually use schlick's approximation to estimate the fresnel constant
	// *fresnel = schlicksApproximation(finish.ior, normal, view);

	// Set to zero to debug. Sad.
	*fresnel = 0;

	*reflCont = (1 - filter) * finish.reflect + filter * *fresnel;
	*transCont = filter * (1 - *fresnel);
	*localCont = (1 - filter) * (1 - finish.reflect);
}

float schlicksApproximation(float ior, Vector normal, Vector view) {
	float F0 = pow(ior - 1, 2) / pow(ior + 1, 2);
	float dot = normal.dot(view);
	float schlicks = F0 + (1 - F0) * pow(1 - dot, 5);
	
	return schlicks;
}

Pigment addReflectionColor(int pw, int ph, vector<Geometry *> *aG, int bounces, float reflCont, Ray ray, Point surface, Vector normal) {
	Pigment reflColor;

	// Is this object reflective?
	if (reflCont > 0) {

		// Find reflected ray
		Ray reflRay = Ray(ray, surface, normal);

		// Send ray into the world to find more color
		reflColor = rayTrace(pw, ph, bounces, aG, reflRay);
	}

	// Otherwise contribute no color
	else {
		reflColor = Pigment(0, 0, 0);
	}

	return reflColor;
}

Pigment addTransmissionColor(int pw, int ph, vector<Geometry *> *aG, int bounces,
	float transCont, Vector initDir, Point surface, Vector normal, Vector view, float ior) {
	Pigment transColor;
	bool exiting;

	// Is this object refractive?
	if (transCont > 0) {

		// Find refracted ray
		Ray refrRay = Ray(surface, initDir, normal, view, 1, ior, &exiting);

		// Is this ray entering or exiting this object?
		if (exiting) {
			normal *= -1;
			ior = 1;
		}

		// Find refracted color
		transColor = rayTrace(pw, ph, bounces, aG, refrRay);
	}

	// Otherwise contribute no color
	else {
		transColor = Pigment(0, 0, 0);
	}

	return transColor;
}

// Color pixel using color_t and my own Pigment class
void colorPixel(int pixelWidth, int pixelHeight, Image *img, Pigment pixel) {
	color_t color;
    setColor(&color, pixel);
    img->pixel(pixelWidth, pixelHeight, color);
}

// fill color_t variable (with Image.cpp compatibility) from my own Pigment class
void setColor(color_t *color, Pigment pixelPigment) {
	color->r = pixelPigment.r * 255;
	color->g = pixelPigment.g * 255;
	color->b = pixelPigment.b * 255;
	color->f = pixelPigment.f;
}
