#ifndef _RAY_TRACE_H_
#define _RAY_TRACE_H_

#define PW 295
#define PH 265

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

void renderLoop(int width, int height, Image *img, vector<Geometry *> *allGeometry, Camera *camera, int bounces);

Pigment rayTrace(int pw, int ph, int bounces, vector<Geometry *> *allGeometry, Ray *ray);

float geometryLoop(int pw, int ph, vector<Geometry *> *allGeometry, float *closestDistance, Ray *ray);

Geometry *initialize(int index, vector<Geometry *> *aG, Ray *ray, float distance, Point *surface, Vector *view, Vector *normal);

Point findSurfacePoint(Ray *ray, float closestDistance);

Pigment findPigment(vector<Geometry *> *aG, Geometry *hitGeom, Ray *ray, int pw, int ph, Vector *view, float distance, Point surface, Vector *normal,
 int bounces);

void setContributions(float *fresnel, float *reflCont, float *transCont, float *localCont, Geometry *hitGeom, Vector *normal, Vector *view);

float schlicksApproximation(float ior, Vector *normal, Vector *view);

Pigment addReflectionColor(float reflCont, Ray *ray, int pw, int ph, int bounces, vector<Geometry *> *aG, Point surface, Vector *normal);

Pigment addTransmissionColor(float transCont, Vector initDir, Point surface, Vector *normal, Vector *view, float ior,
	int pw, int ph, int bounces, vector<Geometry *> *aG);

/* Fill color_t variable (with Image.cpp compatibility) from my own Pigment class */
void setColor(color_t *color, Pigment *pixelPigment);

void colorPixel(int pixelWidth, int pixelHeight, Image *img, Pigment *pixel);








#endif