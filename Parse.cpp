#include "Parse.h"

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

	for (int g = 0; g < allGeometry->size(); g++) {
		allGeometry->at(g)->setLight(*light);
		allGeometry->at(g)->setCamera(*camera);
		allGeometry->at(g)->setAllGeometry(allGeometry);
	}

	return 0;
}

/* Parse through povray file, create setting and geometry */
void parse(fstream *povray, vector<Geometry *> *allGeometry, Camera *camera, Light *light) {
	Sphere *sphere;
	Plane *plane;
	Triangle *triangle;
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
					*camera = Camera();

					// token = strtok(NULL, " \t");
					if (strcmp(token, "l")) {
						povray->getline(line, 99);
						token = strtok(line, " \tlocation<,");
					}
					else {
						token = strtok(NULL, " \tlocation<,");
					}

					float x, y, z;

					/* Fill in Camera center point */
					x = strtof(token, NULL);
					token = strtok(NULL, ", ");
					y = strtof(token, NULL);
					token = strtok(NULL, ", >");
					z = strtof(token, NULL);
					camera->setCenter(Point(x, y, z));

					/* Fill in Camera up vector */
					povray->getline(line, 99);
					token = strtok(line, " \tup<,");
					x = strtof(token, NULL);
					token = strtok(NULL, ", ");
					y = strtof(token, NULL);
					token = strtok(NULL, ", >");
					z = strtof(token, NULL);
					camera->setUp(Vector(x, y, z));

					/* Fill in Camera right vector */
					povray->getline(line, 99);
					token = strtok(line, " \tright<,");
					x = strtof(token, NULL);
					token = strtok(NULL, ", ");
					y = strtof(token, NULL);
					token = strtok(NULL, ", >");
					z = strtof(token, NULL);
					camera->setRight(Vector(x, y, z));

					/* Fill in Camera lookat point */
					povray->getline(line, 99);
					token = strtok(line, " \tlook_at<,");
					x = strtof(token, NULL);
					token = strtok(NULL, ", ");
					y = strtof(token, NULL);
					token = strtok(NULL, ", >}");
					z = strtof(token, NULL);
					camera->setLookAt(Point(x, y, z));

					/* Initialize magnitude of up and right vectors */
				// 	camera->getUp().setMagnitude(camera->getUp());
				// 	camera->getRight().setMagnitude(camera->getRight());
				}
				else if (!strcmp(token, "light_source")) {
					*light = Light();

					float x, y, z;

					/* Fill in Light center point */
					token = strtok(NULL, " {<,");
					x = strtof(token, NULL);
					token = strtok(NULL, " {<,");
					y = strtof(token, NULL);
					token = strtok(NULL, " {<,");
					z = strtof(token, NULL);
					light->setCenter(Point(x, y, z));

					strtok(NULL, " ");
					token = strtok(NULL, " ");

					float r, g, b, f;
					/* Determine if Pigment color is rgb or rgbf */
					rgbf = !strcmp(token, "rgbf");

					/* Fill in Light Pigment */
					token = strtok(NULL, "< ,");
					r = strtof(token, NULL);
					token = strtok(NULL, " ,");
					g = strtof(token, NULL);
					token = strtok(NULL, " ,");
					b = strtof(token, NULL);

					/* Fill in Light Pigment f value */
					if (rgbf) {
						token = strtok(NULL, " >}");
						f = strtof(token, NULL);
					}
					else
						f = 1;

					light->setPigment(Pigment(r, g, b, f));
				}
				else if (!strcmp(token, "sphere")) {
					sphere = new Sphere();

					/* Fill in sphere center point */
					token = strtok(NULL, " {<,");
					float x = strtof(token, NULL);
					token = strtok(NULL, " ,");
					float y = strtof(token, NULL);
					token = strtok(NULL, " >");
					float z = strtof(token, NULL);
					sphere->setCenter(Point(x, y, z));

					/* Fill in sphere radius */
					token = strtok(NULL, " ,");
					sphere->setRadius(strtof(token, NULL));

					/* Fill in sphere Pigment */
					povray->getline(line, 99);
					fillPigment(line, sphere);

					/* Fill in sphere Finish */
					povray->getline(line, 99);
					fillFinish(line, sphere);
					
					/* Add sphere to vector list of geometry */
					allGeometry->push_back(sphere);
				}
				else if (!strcmp(token, "plane")) {
					plane = new Plane();

					/* Fill in plane normal vector */
					token = strtok(NULL, " {<,");
					float x = strtof(token, NULL);
					token = strtok(NULL, " ,");
					float y = strtof(token, NULL);
					token = strtok(NULL, " ,>");
					float z = strtof(token, NULL);
					plane->setNorm(Vector(x, y, z));

					/* Set Magnitude of normal vector */
					// plane->getNorm().setMagnitude(plane->getNorm());
					// plane->getNorm().normalize();

					/* Fill in distance along plane normal */
					token = strtok(NULL, " ,");
					plane->setDistance(strtof(token, NULL));

					/* Fill in plane Pigment */
					povray->getline(line, 99);
					fillPigment(line, plane);

					/* Fill in plane Finish */
					povray->getline(line, 99);
					fillFinish(line, plane);

					/* Add plane to vector list of Geometry */
					allGeometry->push_back(plane);
				}
				else if (!strcmp(token, "triangle")) {
					triangle = new Triangle();

					float x, y, z;
					/* Fill in triangle vertexA */
					povray->getline(line, 99);
					token = strtok(line, " \t{<,");
					x = strtof(token, NULL);
					token = strtok(NULL, " ,");
					y = strtof(token, NULL);
					token = strtok(NULL, " ,>");
					z = strtof(token, NULL);
					triangle->setVertexA(Point(x, y, z));

					/* Fill in triangle vertexB */
					povray->getline(line, 99);
					token = strtok(line, " \t{<,");
					x = strtof(token, NULL);
					token = strtok(NULL, " ,");
					y = strtof(token, NULL);
					token = strtok(NULL, " ,>");
					z = strtof(token, NULL);
					triangle->setVertexB(Point(x, y, z));

					/* Fill in triangle vertexC */
					povray->getline(line, 99);
					token = strtok(line, " \t{<,");
					x = strtof(token, NULL);
					token = strtok(NULL, " ,");
					y = strtof(token, NULL);
					token = strtok(NULL, " ,>");
					z = strtof(token, NULL);
					triangle->setVertexC(Point(x, y, z));

					triangle->setVectors();

					/* Fill in triangle Pigment */
					povray->getline(line, 99);
					fillPigment(line, triangle);

					/* Fill in triangle Finish */
					povray->getline(line, 99);
					fillFinish(line, triangle);

					/* Add triangle to vector list of Geometry */
					allGeometry->push_back(triangle);
				}				
			}
		}
	}
}

void fillPigment(char *line, Geometry *geom) {
	int rgbf;
	char *token;

	token = strtok(line, "pigment {");
	token = strtok(NULL, " ");

	/* Determine if Pigment is rgb or rgbf */
	rgbf = !strcmp(token, "rgbf");

	token = strtok(NULL, " <,");
	float r = strtof(token, NULL);
	token = strtok(NULL, " ,");
	float g = strtof(token, NULL);
	token = strtok(NULL, " ,>}");
	float b = strtof(token, NULL);
	float f;

	if (rgbf) {
		token = strtok(NULL, " ,>}");
		f = strtof(token, NULL);
	}
	else
		f = 0;

	geom->setPigment(Pigment(r, g, b, f));
}

void fillFinish(char *line, Geometry *geom) {
	float amb, dif, spec, rou, refr, refl, ior;
	char finishLine[100], *token;
	int length = 0;

	bool iorFill = false;
	bool roughFill = false;

	amb = dif = spec = refr = refl = 0;
	rou = 0.5;
	ior = 1;

	for (int i = 0, j = 0; i < 80; i++) {
		if (line[i] == '{')
			;
		else {
			finishLine[j++] = line[i];
			length++;
		}
	}
	token = strtok(finishLine, " \t");

	while ((token = strtok(NULL, " \t"))) {
		if (!amb && !strcmp(token, "ambient")) {
			token = strtok(NULL, " \t}");
			amb = strtof(token, NULL);
		}
		else if (!dif && !strcmp(token, "diffuse")) {
			token = strtok(NULL, " \t}");
			dif = strtof(token, NULL);
		}
		else if (!spec && !strcmp(token, "specular")) {
			token = strtok(NULL, " \t}");
			spec = strtof(token, NULL);
		}
		else if (!roughFill && !strcmp(token, "roughness")) {
			token = strtok(NULL, " \t}");
			rou = strtof(token, NULL);
			roughFill = true;
		}
		else if (!refr && !strcmp(token, "refraction")) {
			token = strtok(NULL, " \t}");
			refr = strtof(token, NULL);
		}
		else if (!refl && !strcmp(token, "reflection")) {
			token = strtok(NULL, " \t}");
			refl = strtof(token, NULL);
		}
		else if (!iorFill && !strcmp(token, "ior")) {
			token = strtok(NULL, " \t}");
			ior = strtof(token, NULL);
			iorFill = true;
		}
		//else {
		//	return false;
		//}
	}

	geom->setFinish(Finish(amb, dif, spec, rou, refl, refr, ior));

//	return true;
}