#include "Parse.h"

// #include <stdio.h>
// #include <iostream>
// #include <fstream>
// #include <stdio.h>
// #include <string.h>
// #include <string>
// #include <vector>

using namespace std;

/* Check argc and usage, fill in variables, attempt to open povray file */
int fileOps(int argc, char *argv[], int *width, int *height, string *test, vector<Geometry *> *allGeometry, Camera *camera, Light *light) {
	string fileName;
	fstream povray;

	fileName = argv[3];
	povray.open(fileName, fstream::in);

	/* Attempt to open and parse povray file */
	if (povray.is_open()) {
		parse(&povray, allGeometry, camera, light);
		povray.close();
	}
	else {
		cout << "Error opening file." << endl;
		return 1;
	}

	*width = stoi(argv[1], NULL);
	*height = stoi(argv[2], NULL);
	*test = string(argv[3]);

	return 0;
}

/* Parse through povray file, create setting and geometry */
void parse(fstream *povray, vector<Geometry *> *allGeometry, Camera *camera, Light *light) {
	Sphere *sphere;
	Plane *plane;
	int rgbf;
	char line[100], *token;

	/* While povray file still contains unread lines */
	while (povray->getline(line, 99)) {
		/* Ignore comments in povray file */
		if (line[0] != '/') {
			/* Fill "token" with key words from file */
			token = strtok(line, " \t\n");

			if (token) {
				if (!strcmp(token, "camera")) {
					povray->getline(line, 99);
					*camera = Camera();

					/* Fill in Camera center point */
					token = strtok(line, " \tlocation<,");
					camera->center.setX(strtof(token, NULL));
					token = strtok(NULL, ", ");
					camera->center.setY(strtof(token, NULL));
					token = strtok(NULL, ", >");
					camera->center.setZ(strtof(token, NULL));

					/* Fill in Camera up vector */
					povray->getline(line, 99);
					token = strtok(line, " \tup<,");
					camera->up.setX(strtof(token, NULL));
					token = strtok(NULL, ", ");
					camera->up.setY(strtof(token, NULL));
					token = strtok(NULL, ", >");
					camera->up.setZ(strtof(token, NULL));

					/* Fill in Camera right vector */
					povray->getline(line, 99);
					token = strtok(line, " \tright<,");
					camera->right.setX(strtof(token, NULL));
					token = strtok(NULL, ", ");
					camera->right.setY(strtof(token, NULL));
					token = strtok(NULL, ", >");
					camera->right.setZ(strtof(token, NULL));

					/* Fill in Camera lookat point */
					povray->getline(line, 99);
					token = strtok(line, " \tlook_at<,");
					camera->lookat.setX(strtof(token, NULL));
					token = strtok(NULL, ", ");
					camera->lookat.setY(strtof(token, NULL));
					token = strtok(NULL, ", >");
					camera->lookat.setZ(strtof(token, NULL));

					/* Initialize magnitude of up and right vectors */
					camera->up.setMagnitude(camera->up.getX(), camera->up.getY(), camera->up.getZ());
					camera->right.setMagnitude(camera->right.getX(), camera->right.getY(), camera->right.getZ());
				}
				else if (!strcmp(token, "light_source")) {
					*light = Light();

					/* Fill in Light center point */
					token = strtok(NULL, " {<,");
					light->getCenter()->setX(strtof(token, NULL));
					token = strtok(NULL, " {<,");
					light->getCenter()->setY(strtof(token, NULL));
					token = strtok(NULL, " {<,");
					light->getCenter()->setZ(strtof(token, NULL));

					strtok(NULL, " ");
					token = strtok(NULL, " ");

					/* Determine if Pigment color is rgb or rgbf */
					rgbf = !strcmp(token, "rgbf");

					/* Fill in Light Pigment */
					token = strtok(NULL, "< ,");
					light->getPigment()->setR(strtof(token, NULL));
					token = strtok(NULL, " ,");
					light->getPigment()->setG(strtof(token, NULL));
					token = strtok(NULL, " ,");
					light->getPigment()->setB(strtof(token, NULL));
					
					/* Fill in Light Pigment f value */
					if (rgbf) {
						token = strtok(NULL, " >}");
						light->getPigment()->setF(strtof(token, NULL));
					}
					else
						light->getPigment()->setF(1);
				}
				else if (!strcmp(token, "sphere")) {
					sphere = new Sphere();

					/* Fill in sphere center point */
					token = strtok(NULL, " {<,");
					sphere->center.setX(strtof(token, NULL));
					token = strtok(NULL, " ,");
					sphere->center.setY(strtof(token, NULL));
					token = strtok(NULL, " >");
					sphere->center.setZ(strtof(token, NULL));

					/* Fill in sphere radius */
					token = strtok(NULL, " ,");
					sphere->radius = strtof(token, NULL);

					/* Fill in sphere Pigment */
					povray->getline(line, 99);
					token = strtok(line, " pigment{");
					token = strtok(NULL, " ");

					/* Determine if Pigment color is rgb or rgbf */
					rgbf = !strcmp(token, "rgbf");

					token = strtok(NULL, " <,");
					sphere->pigment.setR(strtof(token, NULL));
					token = strtok(NULL, " ,");
					sphere->pigment.setG(strtof(token, NULL));
					token = strtok(NULL, " ,>}");
					sphere->pigment.setB(strtof(token, NULL));

					if (rgbf) {
						token = strtok(NULL, " ,>}");
						sphere->pigment.setF(strtof(token, NULL));
					}
					else
						sphere->pigment.setF(1);

					/* Fill in sphere Finish */
					povray->getline(line, 99);
					token = strtok(line, "finish {ambient");
					sphere->finish.setAmbient(strtof(token, NULL));
					token = strtok(NULL, "diffuse ");
					sphere->finish.setDiffuse(strtof(token, NULL));

					/* Add sphere to vector list of geometry */
					allGeometry->push_back(sphere);
				}
				else if (!strcmp(token, "plane")) {
					plane = new Plane();

					/* Fill in plane normal vector */
					token = strtok(NULL, " {<,");
					plane->normal.setX(strtof(token, NULL));
					token = strtok(NULL, " ,");
					plane->normal.setY(strtof(token, NULL));
					token = strtok(NULL, " ,>");
					plane->normal.setZ(strtof(token, NULL));

					/* Fill in distance along plane normal */
					token = strtok(NULL, " ,");
					plane->distance = strtof(token, NULL);

					/* Fill in plane Pigment */
					povray->getline(line, 99);
					token = strtok(line, "pigment {");
					token = strtok(NULL, " ");

					/* Determine if Pigment is rgb or rgbf */
					rgbf = !strcmp(token, "rgbf");

					token = strtok(NULL, " <,");
					plane->pigment.setR(strtof(token, NULL));
					token = strtok(NULL, " ,");
					plane->pigment.setG(strtof(token, NULL));
					token = strtok(NULL, " ,>}");
					plane->pigment.setB(strtof(token, NULL));

					if (rgbf) {
						token = strtok(NULL, " ,>}");
						plane->pigment.setF(strtof(token, NULL));
					}
					else
						plane->pigment.setF(1);

					/* Fill in plane Finish */
					povray->getline(line, 99);
					token = strtok(line, "finish {ambient");
					plane->finish.setAmbient(strtof(token, NULL));
					token = strtok(NULL, "diffuse ");
					plane->finish.setDiffuse(strtof(token, NULL));

					/* Set Magnitude of normal vector */
					plane->normal.setMagnitude(plane->normal.getX(), plane->normal.getY(), plane->normal.getZ());
					
					/* Add plane to vector list of Geometry */
					allGeometry->push_back(plane);
				}
			}
		}
	}
}