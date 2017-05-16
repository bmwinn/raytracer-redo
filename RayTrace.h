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
	color->r = pixelPigment->getR() * 255;
	color->g = pixelPigment->getG() * 255;
	color->b = pixelPigment->getB() * 255;
	color->f = pixelPigment->getF();
}

void resetBlinnPhongPigments(vector<Geometry *> *allGeometry) {
	for (int g = 0; g < allGeometry->size(); g++) {
		allGeometry->at(g)->getPigmentA()->reset();
		allGeometry->at(g)->getPigmentD()->reset();
		allGeometry->at(g)->getPigmentS()->reset();
		allGeometry->at(g)->getPixel()->reset();
	}
}

void colorPixel(int pixelWidth, int pixelHeight, Pigment *pixelPigment, Image *img, Geometry *curGeom) {
	color_t color;
    pixelPigment = curGeom->getPixel();
    setColor(&color, pixelPigment);
    img->pixel(pixelWidth, pixelHeight, color);
}

void colorPixel(int pixelWidth, int pixelHeight, Image *img, Geometry *curGeom) {
	color_t color;
    setColor(&color, curGeom->getPixel());
    if (pixelWidth == 420 && pixelHeight == 130) {
    	cout << "color: " << color.r << " " << color.g << " " << color.b << " " << color.f << endl;
    }
    img->pixel(pixelWidth, pixelHeight, color);
}

float geometryLoop(int pixelWidth, int pixelHeight, Image *img, Ray *ray, vector<Geometry *> *allGeometry) {
	float distance, closestDistance = 10000;
	int geomIndex = 0;

	for (int i = 0; i < allGeometry->size(); i++) {
		Geometry *curGeom = allGeometry->at(i);
		distance = curGeom->intersect(ray);

		if (distance > 0.0001 && distance < closestDistance) {
			closestDistance = distance;
			geomIndex = i;
		}
	}

	if (closestDistance > 0.0001) {
		Geometry *curGeom = allGeometry->at(geomIndex);
		curGeom->blinnPhong(ray, closestDistance);
		colorPixel(pixelWidth, pixelHeight, img, curGeom);
		if (pixelWidth == 420 && pixelHeight == 130) {
			cout << "t = " << closestDistance << endl;
			cout << "pixel: [" << pixelWidth << ", " << pixelHeight << "]" << endl;
			ray->print();
			curGeom->getPigmentA()->print();
			curGeom->getPigmentD()->print();
			curGeom->getPigmentS()->print();
			cout << "curgeom pixel ";
			curGeom->getPixel()->print();
			cout << endl;
		}		
	}
	else if (pixelWidth == 420 and pixelHeight == 130) {
		cout << "no hit" << endl;
	}

	return geomIndex;
}

void rayTrace(int width, int height, Camera *camera, Light *light, Image *img, vector<Geometry *> *allGeometry, string test) {
	float closestDistance;
	int intGeom;
	color_t black = {0, 0, 0, 0};

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Ray *ray = new Ray(i, j, width, height, camera);

			img->pixel(i, j, black);

			if (i == 420 && j == 130) {
				cout << "shadow" << endl;
			}

			intGeom = geometryLoop(i, j, img, ray, allGeometry);

			//printUnitTest(&test, i, j, closestDistance, ray, pixelPigment, &color);
			//printUnitTest2(&test, i, j, intGeom, closestDistance, ray, allGeometry->at(intGeom), light, camera);

			resetBlinnPhongPigments(allGeometry);
			// if (i == 420 and j == 130) {
			// 	cout << "reset bp..." << endl;
			// 	allGeometry->at(0)->getPigmentA()->print();
			// 	allGeometry->at(0)->getPigmentD()->print();
			// 	allGeometry->at(0)->getPigmentS()->print();

			// 	allGeometry->at(1)->getPigmentA()->print();
			// 	allGeometry->at(1)->getPigmentD()->print();
			// 	allGeometry->at(1)->getPigmentS()->print();
			// }
		}
	}
}

#endif