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
		allGeometry->at(g)->setLight(light);
		allGeometry->at(g)->setCamera(camera);
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
					/* Fill in Camera center point */
					camera->getCenter()->x = strtof(token, NULL);
					token = strtok(NULL, ", ");
					camera->getCenter()->y = strtof(token, NULL);
					token = strtok(NULL, ", >");
					camera->getCenter()->z = strtof(token, NULL);

					/* Fill in Camera up vector */
					povray->getline(line, 99);
					token = strtok(line, " \tup<,");
					camera->getUp()->x = strtof(token, NULL);
					token = strtok(NULL, ", ");
					camera->getUp()->y = strtof(token, NULL);
					token = strtok(NULL, ", >");
					camera->getUp()->z = strtof(token, NULL);

					/* Fill in Camera right vector */
					povray->getline(line, 99);
					token = strtok(line, " \tright<,");
					camera->getRight()->x = strtof(token, NULL);
					token = strtok(NULL, ", ");
					camera->getRight()->y = strtof(token, NULL);
					token = strtok(NULL, ", >");
					camera->getRight()->z = strtof(token, NULL);

					/* Fill in Camera lookat point */
					povray->getline(line, 99);
					token = strtok(line, " \tlook_at<,");
					camera->getLookAt()->x = strtof(token, NULL);
					token = strtok(NULL, ", ");
					camera->getLookAt()->y = strtof(token, NULL);
					token = strtok(NULL, ", >}");
					camera->getLookAt()->z = strtof(token, NULL);

					/* Initialize magnitude of up and right vectors */
					camera->getUp()->setMagnitude(camera->getUp());
					camera->getRight()->setMagnitude(camera->getRight());
				}
				else if (!strcmp(token, "light_source")) {
					*light = Light();

					/* Fill in Light center point */
					token = strtok(NULL, " {<,");
					light->getCenter()->x = strtof(token, NULL);
					token = strtok(NULL, " {<,");
					light->getCenter()->y = strtof(token, NULL);
					token = strtok(NULL, " {<,");
					light->getCenter()->z = strtof(token, NULL);

					strtok(NULL, " ");
					token = strtok(NULL, " ");

					/* Determine if Pigment color is rgb or rgbf */
					rgbf = !strcmp(token, "rgbf");

					/* Fill in Light Pigment */
					token = strtok(NULL, "< ,");

					light->getPigment()->r = strtof(token, NULL);
					token = strtok(NULL, " ,");
					light->getPigment()->g = strtof(token, NULL);
					token = strtok(NULL, " ,");
					light->getPigment()->b = strtof(token, NULL);
					
					/* Fill in Light Pigment f value */
					if (rgbf) {
						token = strtok(NULL, " >}");
						light->getPigment()->f = strtof(token, NULL);
					}
					else
						light->getPigment()->f = 1;
				}
				else if (!strcmp(token, "sphere")) {
					sphere = new Sphere();

					/* Fill in sphere center point */
					token = strtok(NULL, " {<,");
					sphere->getCenter()->x = strtof(token, NULL);
					token = strtok(NULL, " ,");
					sphere->getCenter()->y = strtof(token, NULL);
					token = strtok(NULL, " >");
					sphere->getCenter()->z = strtof(token, NULL);

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
					plane->getNorm()->x = strtof(token, NULL);
					token = strtok(NULL, " ,");
					plane->getNorm()->y = strtof(token, NULL);
					token = strtok(NULL, " ,>");
					plane->getNorm()->z = strtof(token, NULL);

					/* Set Magnitude of normal vector */
					plane->getNorm()->setMagnitude(plane->getNorm());
					plane->getNorm()->normalize();

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

					/* Fill in triangle vertexA */
					povray->getline(line, 99);
					token = strtok(line, " \t{<,");
					triangle->getVertexA()->x = strtof(token, NULL);
					token = strtok(NULL, " ,");
					triangle->getVertexA()->y = strtof(token, NULL);
					token = strtok(NULL, " ,>");
					triangle->getVertexA()->z = strtof(token, NULL);

					/* Fill in triangle vertexB */
					povray->getline(line, 99);
					token = strtok(line, " \t{<,");
					triangle->getVertexB()->x = strtof(token, NULL);
					token = strtok(NULL, " ,");
					triangle->getVertexB()->y = strtof(token, NULL);
					token = strtok(NULL, " ,>");
					triangle->getVertexB()->z = strtof(token, NULL);

					/* Fill in triangle vertexC */
					povray->getline(line, 99);
					token = strtok(line, " \t{<,");
					triangle->getVertexC()->x = strtof(token, NULL);
					token = strtok(NULL, " ,");
					triangle->getVertexC()->y = strtof(token, NULL);
					token = strtok(NULL, " ,>");
					triangle->getVertexC()->z = strtof(token, NULL);

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
	geom->getPigment()->r = strtof(token, NULL);
	token = strtok(NULL, " ,");
	geom->getPigment()->g = strtof(token, NULL);
	token = strtok(NULL, " ,>}");
	geom->getPigment()->b = strtof(token, NULL);

	if (rgbf) {
		token = strtok(NULL, " ,>}");
		geom->getPigment()->f = strtof(token, NULL);
	}
	else
		geom->getPigment()->f = 0;
}

void fillFinish(char *line, Geometry *geom) {
	char finishLine[100], *token;
	int length = 0;

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
		if (!geom->getFinish()->ambient && !strcmp(token, "ambient")) {
			token = strtok(NULL, " \t}");;
			geom->getFinish()->ambient = strtof(token, NULL);
		}
		else if (!geom->getFinish()->diffuse && !strcmp(token, "diffuse")) {
			token = strtok(NULL, " \t}");
			geom->getFinish()->diffuse = strtof(token, NULL);
		}
		else if (!geom->getFinish()->specular && !strcmp(token, "specular")) {
			token = strtok(NULL, " \t}");
			geom->getFinish()->specular = strtof(token, NULL);
		}
		else if (!strcmp(token, "roughness")) {
			token = strtok(NULL, " \t}");
			geom->getFinish()->roughness = strtof(token, NULL);
		}
		else if (!geom->getFinish()->refract && !strcmp(token, "refraction")) {
			token = strtok(NULL, " \t}");
			geom->getFinish()->refract = strtof(token, NULL);
		}
		else if (!geom->getFinish()->reflect && !strcmp(token, "reflection")) {
			token = strtok(NULL, " \t}");
			geom->getFinish()->reflect = strtof(token, NULL);
		}
		else if (!strcmp(token, "ior")) {
			token = strtok(NULL, " \t}");
			geom->getFinish()->ior = strtof(token, NULL);
		}
		//else {
		//	return false;
		//}
	}

//	return true;
}