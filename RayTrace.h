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

void resetBlinnPhongPigments(vector<Geometry *> *allGeometry) {
	for (int g = 0; g < allGeometry->size(); g++) {
		allGeometry->at(g)->getPigmentA()->reset();
		allGeometry->at(g)->getPigmentD()->reset();
		allGeometry->at(g)->getPigmentS()->reset();
		allGeometry->at(g)->getPixel()->reset();
	}
}

void colorPixel(int pixelWidth, int pixelHeight, Image *img, Geometry *curGeom) {
	color_t color;
    setColor(&color, curGeom->getPixel());
    img->pixel(pixelWidth, pixelHeight, color);
}

void colorPixel(int pixelWidth, int pixelHeight, Image *img, Pigment *pixel) {
	color_t color;
    setColor(&color, pixel);
    img->pixel(pixelWidth, pixelHeight, color);
}
/*
float geometryLoop(int pixelWidth, int pixelHeight, Image *img, Ray *ray, vector<Geometry *> *allGeometry) {
	float distance, closestDistance = 10000;
	color_t black = {0, 0, 0, 1};
	int geomIndex = 0;

	for (int i = 0; i < allGeometry->size(); i++) {
		Geometry *curGeom = allGeometry->at(i);
		distance = curGeom->intersect(ray);

		if (distance > 0.0001 && distance < closestDistance) {
			closestDistance = distance;
			geomIndex = i;
		}
	}

	if (closestDistance < 10000 && closestDistance > 0.0001) {
		Geometry *curGeom = allGeometry->at(geomIndex);
		curGeom->blinnPhong(ray, closestDistance);
		colorPixel(pixelWidth, pixelHeight, img, curGeom);
	}
	else {
		img->pixel(pixelWidth, pixelHeight, black);
	}

	return geomIndex;
}*/

/*void rayTrace(int width, int height, Camera *camera, Light *light, Image *img, vector<Geometry *> *allGeometry, string test) {
	int intGeom;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Ray *ray = new Ray(i, j, width, height, camera);

			intGeom = geometryLoop(i, j, img, ray, allGeometry);

			//printUnitTest(&test, i, j, closestDistance, ray, pixelPigment, &color);
			//printUnitTest2(&test, i, j, intGeom, closestDistance, ray, allGeometry->at(intGeom), light, camera);

			resetBlinnPhongPigments(allGeometry);
		}
	}
}*/

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
			distance = curGeom->intersect(ray);
			if (distance > 0.0001 && distance < closestDistance) {
				closestDistance = distance;
				geomIndex = i;
			}
		}

		if (pw == 120 and ph == 120) cout << "on bounce " << bounces << ", closest item is object " << geomIndex << endl; 
		if (closestDistance == 10000) {
			if (pw == 120 and ph == 120)
				cout << "finished recursing" << endl;
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

		curGeom->blinnPhong(ray, closestDistance);

		Pigment reflectionColor, transmissionColor;
		if (reflectionContribution > 0) {
			Ray *reflectRay = new Ray(ray, surface, curGeom->getNormal());
			reflectionColor = rayTrace(pw, ph, bounces, allGeometry, reflectRay);
		}
		else {
			if (pw == 120 and ph == 120)
				cout << "no reflection" << endl;
			reflectionColor = black;
		}

		if (transmissionContribution > 0) {
			if (pw == 120 and ph == 120) {
				finish->print();
			}
			Ray *refractRay = new Ray(surface, *ray->getDirection(), *curGeom->getNormal(), &view, 1, finish->ior);			
			transmissionColor = rayTrace(pw, ph, bounces, allGeometry, refractRay);
		}
		else {
			if (pw == 120 and ph == 120)
				cout << "no refraction" << endl;
			transmissionColor = black;
		}

		Pigment localColor = *curGeom->getPixel();
		resetBlinnPhongPigments(allGeometry);
		if (pw == 120 and ph == 120) {
			cout << "pigment A: "; curGeom->getPigmentA()->print();
			cout << "pigment D: "; curGeom->getPigmentD()->print();
			cout << "pigment S: "; curGeom->getPigmentS()->print();
			cout << "local color "; localColor.print();
			cout << "local cont " << localContribution << endl;
			cout << "refl color "; reflectionColor.print();
			cout << "refl cont " << reflectionContribution << endl;
			cout << "refr color "; transmissionColor.print();
			cout << "refr cont " << transmissionContribution << endl;
		}

		Pigment totalColor = localColor * localContribution +
								reflectionColor * reflectionContribution +
								transmissionColor * transmissionContribution;

		if (pw == 120 and ph == 120) {
			totalColor.print();
		}

		return totalColor;
	}
	else { return black; }
}

void renderLoop(int width, int height, Image *img, vector<Geometry *> *allGeometry, Camera *camera) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Ray *ray = new Ray(i, j, width, height, camera);
			Pigment fill = rayTrace(i, j, 5, allGeometry, ray);
			if (i == 120 and j == 120) {
				cout << endl << "render loop: pigment ";
				fill.print();
			}
			colorPixel(i, j, img, &fill);
		}
	}
}

#endif