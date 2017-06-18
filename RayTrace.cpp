#include "RayTrace.h"

// send a ray to each pixel in the result image
void renderLoop(int width, int height, Image *img, vector<Geometry *> *allGeometry, Camera camera, int bounces) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {

			// create a ray from the camera towards pixel
			Ray ray = Ray(i, j, width, height, camera);
			
			if (i == PW and j == PH)
				cout << "Iteration type: Primary" << endl;

			// find the color at this pixel location by ray tracing
			Pigment fill = rayTrace(i, j, bounces, allGeometry, ray);

			if (i == PW and j == PH)
				cout << "Pixel [" << i << ", " << j << "] Color: (" << fill.r << " " << fill.g << " " << fill.b << ")" << endl;
			
			// fill in this pixel with the color found
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

	// check recursion, if we have bounced too many times, return black
	if (bounces-- > 0) {

		// loop through list of geometry, check which geometry object this ray hits, if any
		geomIndex = geometryLoop(pw, ph, allGeometry, &closestDistance, ray);

		// if this ray didn't hit anything, return black
		if (geomIndex == -1)
			return black;

		// now that we know which geometry object we hit, initialize view vector, surface point, normal vector
		view = initialize(hitGeom, &surface, &normal, geomIndex, allGeometry, ray, closestDistance);

		// find the color of what we hit (includes recursive call to rayTrace)
		Pigment totalColor = findPigment(pw, ph, allGeometry, hitGeom, bounces, ray, view, closestDistance, surface, normal);
		return totalColor;
	}
	else {
		return black;
	}
}

// find the closest geometry object, return its index in the list of geometry objects
float geometryLoop(int pw, int ph, vector<Geometry *> *allGeometry, float *closestDistance, Ray ray) {
	float distance;
	int geomIndex = -1;

	for (int i = 0; i < allGeometry->size(); i++) {
		Geometry *curGeom = allGeometry->at(i);

		// find the distance along this ray towards this geometry object
		distance = curGeom->intersect(pw, ph, ray);

		// if the distance is positive and smaller than the closest found distance, update
		if (distance > 0.0001 && distance < *closestDistance) {
			*closestDistance = distance;
			geomIndex = i;
		}
	}

	return geomIndex;
}

// initialize surface point, normal vector, view vector
Vector initialize(Geometry *&hitGeom, Point *surface, Vector *normal, int index, vector<Geometry *> *aG, Ray ray, float distance) {
	// keep track of which geometry object was intersected
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

// Pigment at a pixel comes from local geometry color, reflected color, and refracted color
Pigment findPigment(int pw, int ph, vector<Geometry *> *aG, Geometry *hitGeom, int bounces,
	Ray ray, Vector view, float distance, Point surface, Vector normal) {
	float fresnel, reflCont, transCont, localCont;
	Pigment localP, reflP, transP;
	float ior = hitGeom->getFinish().ior;

	// initialize constants
	setContributions(&fresnel, &reflCont, &transCont, &localCont, hitGeom, normal, view);

	// find local pigment color through Blinn Phong BRDF
	localP = hitGeom->blinnPhong(pw, ph, ray, distance, surface, normal);

	// find reflected pigment color, keeping track of number of bounces (includes recursive call to rayTrace)
	reflP = addReflectionColor(pw, ph, aG, bounces, reflCont, ray, surface, normal);

	// find refracted pigment color, keeping track of number of bounces (includes recursive call to rayTrace)
	transP = addTransmissionColor(pw, ph, aG, bounces, transCont, ray.getDirection(), surface, normal, view, ior);

	// add contributions from local, reflected, and refracted colors
	Pigment totalColor = localP * localCont + reflP * reflCont + transP * transCont;

	return totalColor;
}

void setContributions(float *fresnel, float *reflCont, float *transCont, float *localCont, Geometry *hitGeom, Vector normal, Vector view) {
	Finish finish = hitGeom->getFinish();
	float filter = hitGeom->getPigment().f;

	// eventually use schlick's approximation to estimate the fresnel constant
	// *fresnel = schlicksApproximation(finish.ior, normal, view);

	// set to zero to debug
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

	// if this geometry object is reflective, contribute reflective color
	if (reflCont > 0) {
		// find ray reflected off this geometry object based on its surface point and normal
		Ray reflRay = Ray(ray, surface, normal);

		if (pw == PW and ph == PH)
			cout << "Iteration type: Reflection" << endl;

		// find its reflected color
		reflColor = rayTrace(pw, ph, bounces, aG, reflRay);
	}

	// otherwise contribute no color
	else {
		reflColor = Pigment(0, 0, 0);
	}

	return reflColor;
}

Pigment addTransmissionColor(int pw, int ph, vector<Geometry *> *aG, int bounces,
	float transCont, Vector initDir, Point surface, Vector normal, Vector view, float ior) {
	Pigment transColor;
	bool exiting;

	// if this geometry object is refractive, contribute refractive color
	if (transCont > 0) {
		if (pw == PW and ph == PH) {
			cout << "Iteration type: Refraction" << endl;
		}

		// find ray refracted through this geometry object
		Ray refrRay = Ray(surface, initDir, normal, view, 1, ior, &exiting);

		if (exiting) {
			normal *= -1;
			ior = 1;
		}

		// find refracted color
		transColor = rayTrace(pw, ph, bounces, aG, refrRay);
	}

	// otherwise contribute no color
	else {
		transColor = Pigment(0, 0, 0);
	}

	return transColor;
}

// color pixel using color_t and my own Pigment class
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
