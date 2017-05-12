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
					povray->getline(line, 99);
					*camera = Camera();

					/* Fill in Camera center point */
					token = strtok(line, " \tlocation<,");
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
					token = strtok(NULL, ", >");
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
					plane->getNormal()->x = strtof(token, NULL);
					token = strtok(NULL, " ,");
					plane->getNormal()->y = strtof(token, NULL);
					token = strtok(NULL, " ,>");
					plane->getNormal()->z = strtof(token, NULL);

					/* Set Magnitude of normal vector */
					plane->getNormal()->setMagnitude(plane->getNormal());
					plane->getNormal()->normalize();

					/* Fill in distance along plane normal */
					token = strtok(NULL, " ,");
					plane->setDistance(strtof(token, NULL));

					plane->setOnGeom();

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
	geom->getPigment()->setR(strtof(token, NULL));
	token = strtok(NULL, " ,");
	geom->getPigment()->setG(strtof(token, NULL));
	token = strtok(NULL, " ,>}");
	geom->getPigment()->setB(strtof(token, NULL));

	if (rgbf) {
		token = strtok(NULL, " ,>}");
		geom->getPigment()->setF(strtof(token, NULL));
	}
	else
		geom->getPigment()->setF(1);
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
		if (!geom->getFinish()->getAmbient() && !strcmp(token, "ambient")) {
			token = strtok(NULL, " \t}");;
			geom->getFinish()->setAmbient(strtof(token, NULL));
		}
		else if (!geom->getFinish()->getDiffuse() && !strcmp(token, "diffuse")) {
			token = strtok(NULL, " \t}");
			geom->getFinish()->setDiffuse(strtof(token, NULL));
		}
		else if (!geom->getFinish()->getSpecular() && !strcmp(token, "specular")) {
			token = strtok(NULL, " \t}");
			geom->getFinish()->setSpecular(strtof(token, NULL));
		}
		else if (!strcmp(token, "roughness")) {
			token = strtok(NULL, " \t}");
			geom->getFinish()->setRoughness(strtof(token, NULL));
		}
		else if (!geom->getFinish()->getRefract() && !strcmp(token, "refraction")) {
			token = strtok(NULL, " \t}");
			geom->getFinish()->setRefract(strtof(token, NULL));
		}
		else if (!geom->getFinish()->getReflect() && !strcmp(token, "reflection")) {
			token = strtok(NULL, " \t}");
			geom->getFinish()->setReflect(strtof(token, NULL));
		}
		else if (!geom->getFinish()->getIor() && !strcmp(token, "ior")) {
			token = strtok(NULL, " \t}");
			geom->getFinish()->setIor(strtof(token, NULL));
		}
		//else {
		//	return false;
		//}
	}

//	return true;
}