#ifndef _RAY_TRACE_H_
#define _RAY_TRACE_H_

#include "Parse.h"
#include "Image.h"
// #include "UnitTest.h"

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
void setColor(color_t *color, Pigment *pixelPigment);

void colorPixel(int pixelWidth, int pixelHeight, Image *img, Pigment *pixel);

float schlicksApproximation(float ior, Vector *normal, Vector *view);

float geometryLoop(int pw, int ph, vector<Geometry *> *allGeometry, float *closestDistance, Ray *ray);

void setContributions(float *fresnel, float *reflCont, float *transCont, float *localCont, Geometry *curGeom, Vector *view);

Point findSurfacePoint(Geometry *curGeom, Ray *ray, float closestDistance);

Geometry *initialize(int index, vector<Geometry *> *aG, Ray *ray, float distance, Point *surface, Vector *view);

Pigment addReflectionColor(float reflCont, Ray *ray, int pw, int ph, int bounces, vector<Geometry *> *aG, Point surface, Vector *normal);

Pigment addTransmissionColor(float transCont, Vector initDir, Point surface, Vector normal, Vector *view, float ior,
	int pw, int ph, int bounces, vector<Geometry *> *aG);

Pigment rayTrace(int pw, int ph, int bounces, vector<Geometry *> *allGeometry, Ray *ray);

void renderLoop(int width, int height, Image *img, vector<Geometry *> *allGeometry, Camera *camera, int bounces);

Pigment findPigment(vector<Geometry *> *aG, Geometry *hitGeom, Ray *ray, int pw, int ph, Vector view, float distance, Point surface, int bounces);

#endif