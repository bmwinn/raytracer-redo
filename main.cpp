// TODO
// rethink fileops?
// 

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

int main(int argc, char *argv[]) {
	int width, height, intGeom;
	string input, outTGA;
	float distance, closestDistance;
	string test;
	Light light;
	Camera camera;
	color_t color, black = {0, 0, 0, 0};
	vector<Geometry *> allGeometry;

	string p = "Plane";

	if (argc != 5) {
		cout << "Error. Usage: ./raytrace <width> <height> <input_file> <output_directory>" << endl;
		return 1;
	}

	input = argv[3];
	outTGA = argv[4];
	outTGA += "/";
	for (int i = 0; i < input.size(); i++) {
		if (input.at(i) == '.')
			i = input.size();
		else
			outTGA += input.at(i);
	}
	outTGA += ".tga";

	/* Attempt to open .pov file, fill in variables, and create geometry */
	if (fileOps(argc, argv, &width, &height, &test, &allGeometry, &camera, &light)) {
		/* Otherwise, fileOps prints error message. Quit program. */
		return 1;
	}

	Image img(width, height);

	/* Loop through pixels */
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++) {
			Ray *ray = new Ray(i, j, width, height, &camera);
			closestDistance = 10000;
			intGeom = 0;
			Pigment *pixelPigment = new Pigment();

			/* Initialize current pixel to background color */
			img.pixel(i, j, black);

			/* Loop through geometry */
			for (int g = 0; g < allGeometry.size(); g++) {
				Geometry *curGeom = allGeometry.at(g);
				/* CurGeom set to fill pixel */
				curGeom->setPixel(pixelPigment);
				/* Find distance along ray to current geometry */
				distance = curGeom->intersect(ray);

				/* Update closest distance from camera to geometry */
				if (distance > 0 && distance < closestDistance) {
				    closestDistance = distance;
				    intGeom = g;
				    pixelPigment->reset();
				    curGeom->blinnPhong(ray, closestDistance);
				    pixelPigment->setColorT(&color);
				    setColor(&color, pixelPigment);

					/* Update current pixel color to geometry color */
				    img.pixel(i, j, color);
				}
			}

			/* Print unit test results */ 
			// printUnitTest(&test, i, j, closestDistance, ray, pixelPigment, &color);
			// printUnitTest2(&test, i, j, intGeom, closestDistance, ray, allGeometry.at(intGeom), &light, &camera);

			for (int g = 0; g < allGeometry.size(); g++) {
				allGeometry.at(g)->getPigmentA()->reset();
				allGeometry.at(g)->getPigmentD()->reset();
				allGeometry.at(g)->getPigmentS()->reset();
			}
		}
	}

	img.WriteTga((char *)outTGA.c_str(), true);

	return 0;
}
