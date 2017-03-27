#pragma once
#include <vector>
#include "objs.h"
using namespace std;

/* Open .pov file, fill in variables, and create geometry */
int fileOps(int argc, char *argv[], int *width, int *height, string *test, vector<Geometry *> *allGeometry, Camera *camera, Light *light);

/* Once .pov file is open, parse through */
void parse(fstream *povray, vector<Geometry *> *allGeometry, Camera *camera, Light *light);