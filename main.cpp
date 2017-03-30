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
#include <cmath>

using namespace std;

/* Fill color_t variable (with Image.cpp compatibility) from my own Pigment class */
void setColor(color_t *color, Pigment *pixelPigment) {
	color->r = pixelPigment->r * 255;
	color->g = pixelPigment->g * 255;
	color->b = pixelPigment->b * 255;
	color->f = pixelPigment->f;
}

int main(int argc, char *argv[]) {
	int width, height;
	string input, outTGA;
	float distance, closestDistance;
	string test;
	Light light;
	Camera camera;
	color_t color, black = {0, 0, 0, 0};
	vector<Geometry *> allGeometry;

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
	if (fileOps(argc, argv, &width, &height, &test, &allGeometry, &camera, &light))
		/* Otherwise, fileOps prints error message. Quit program. */
		return 1;

	Image img(width, height);

	/* Loop through pixels */
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++) {
			Ray ray = Ray(i, j, width, height, &camera);
			Pigment pixelPigment = Pigment();
			closestDistance = 10000;

			/* Initialize current pixel to background color */
			img.pixel(i, j, black);

			/* Loop through geometry */
			for (int g = 0; g < allGeometry.size(); g++) {
				/* Find distance along ray to current geometry */
				distance = allGeometry.at(g)->Intersect(&ray, &camera);

				/* Update closest distance from camera to geometry */
				if (distance > 0 && distance < closestDistance) {
				   closestDistance = distance;
				   pixelPigment = allGeometry.at(g)->pigment;
					setColor(&color, &pixelPigment);

					/* Update current pixel color to geometry color */
					img.pixel(i, j, color);
				}
			}

			/* Print unit test results */ 
			printUnitTest(&test, i, j, closestDistance, &ray, &pixelPigment, &color);
		}
	}

	img.WriteTga((char *)outTGA.c_str(), true);

	return 0;
}




