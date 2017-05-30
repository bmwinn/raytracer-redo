#ifndef _RAY_TRACE_H_
#define _RAY_TRACE_H_

#include "Parse.h"
#include "Image.h"
#include "UnitTest.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

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

float schlicksApproximation(float ior, Vector *normal, Vector *view) {
	float F0 = pow(ior - 1, 2) / pow(ior + 1, 2);
	float schlicks = F0 + (1 - F0) * (1 - pow(normal->dot(view), 5));
	return schlicks;
}




Pigment rayTrace(int pw, int ph, int bounces, vector<Geometry *> *allGeometry, Ray *ray) {
	float distance, closestDistance;
	int geomIndex = -1;
	Pigment black = Pigment(0, 0, 0);
	// watch out for when you decrement bounces

	if (bounces > 0) {
		bounces--;
		closestDistance = 10000;

		for (int i = 0; i < allGeometry->size(); i++) {
			Geometry *curGeom = allGeometry->at(i);
			distance = curGeom->intersect(pw, ph, ray);
			if (distance > 0.0001 && distance < closestDistance) {
				closestDistance = distance;
				geomIndex = i;
			}
		}

		if (geomIndex == -1) {
			return black;
		}

		Geometry *curGeom = allGeometry->at(geomIndex);
		Point surface = *ray->getStart();
		surface += *ray->getDirection() * closestDistance;

		Finish *finish = curGeom->getFinish();
		Pigment *pigment = curGeom->getPigment();
		Vector view = *curGeom->getCamera()->getCenter() - surface;

		float fresnelReflectance = schlicksApproximation(finish->ior, curGeom->getNormal(), &view);

		float reflectionContribution = (1 - pigment->f) * finish->reflect + pigment->f * fresnelReflectance;
		float transmissionContribution = pigment->f * (1 - fresnelReflectance);
		float localContribution = (1 - pigment->f) * (1 - finish->reflect);

		Pigment localColor = curGeom->blinnPhong(pw, ph, ray, closestDistance, surface);

		Pigment reflectionColor, transmissionColor;
		if (reflectionContribution > 0) {
			Ray *reflectRay = new Ray(ray, surface, curGeom->getNormal());
			reflectionColor = rayTrace(pw, ph, bounces, allGeometry, reflectRay);
		}
		else {
			reflectionColor = black;
		}

		if (transmissionContribution > 0) {
			Ray *refractRay = new Ray(surface, *ray->getDirection(), *curGeom->getNormal(), &view, 1, finish->ior);			
			transmissionColor = rayTrace(pw, ph, bounces, allGeometry, refractRay);
		}
		else {
			transmissionColor = black;
		}

		Pigment totalColor = localColor * localContribution +
								reflectionColor * reflectionContribution +
								transmissionColor * transmissionContribution;

		return totalColor;
	}
	else {
		return black;
	}
}

void renderLoop(int width, int height, Image *img, vector<Geometry *> *allGeometry, Camera *camera) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Ray *ray = new Ray(i, j, width, height, camera);
			Pigment fill = rayTrace(i, j, 5, allGeometry, ray);
			colorPixel(i, j, img, &fill);
		}
	}
}

#endif