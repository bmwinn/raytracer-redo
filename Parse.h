#ifndef _PARSE_H_
#define _PARSE_H_

#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Light.h"
#include "Camera.h"
#include "Geometry.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"

using namespace std;

/* Open .pov file, fill in variables, and create geometry */
int fileOps(int argc, char *argv[], int *width, int *height, string *test, vector<Geometry *> *allGeometry, Camera *camera, Light *light);

/* Once .pov file is open, parse through */
void parse(fstream *povray, vector<Geometry *> *allGeometry, Camera *camera, Light *light);

void fillPigment(char *line, Geometry *geom);

void fillFinish(char *line, Geometry *geom);

#endif