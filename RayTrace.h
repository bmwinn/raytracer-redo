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
}

void rayTrace(int width, int height, Camera *camera, Light *light, Image *img, vector<Geometry *> *allGeometry, string test) {
	float closestDistance;
	int intGeom;
	color_t black = {0, 0, 0, 1};

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Ray *ray = new Ray(i, j, width, height, camera);

			intGeom = geometryLoop(i, j, img, ray, allGeometry);

			//printUnitTest(&test, i, j, closestDistance, ray, pixelPigment, &color);
			//printUnitTest2(&test, i, j, intGeom, closestDistance, ray, allGeometry->at(intGeom), light, camera);

			resetBlinnPhongPigments(allGeometry);
		}
	}
}

#endif