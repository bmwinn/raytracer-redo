// TODO
// rethink fileops?
#include "RayTrace.h"

int main(int argc, char *argv[]) {
	// int width, height, intGeom;
	int width, height;
	string input, outTGA;
	// float distance, closestDistance;
	string test;
	Light light;
	Camera camera;
	// color_t color, black = {0, 0, 0, 0};
	vector<Geometry *> allGeometry;

	// string p = "Plane";

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
	rayTrace(width, height, &camera, &light, &allGeometry, &img, test);
// void rayTrace(int width, int height, Camera *camera, Light *light, Image *img, vector<Geometry *> *allGeometry, string test) {

	img.WriteTga((char *)outTGA.c_str(), true);

	/* Loop through pixels */
	// for (int i = 0; i < width; i++){
	// 	for (int j = 0; j < height; j++) {
	// 		Ray *ray = new Ray(i, j, width, height, &camera);
	// 		closestDistance = 10000;
	// 		intGeom = 0;
	// 		Pigment *pixelPigment = new Pigment();

	// 		img.pixel(i, j, black);

	// 		/* Loop through geometry */
	// 		for (int g = 0; g < allGeometry.size(); g++) {
	// 			Geometry *curGeom = allGeometry.at(g);
	// 			distance = curGeom->intersect(ray);

	// 			 Update closest distance from camera to geometry 
	// 			if (distance > 0 && distance < closestDistance) {
	// 			    closestDistance = distance;
	// 			    intGeom = g;

	// 			    pixelPigment->reset();
	// 			    curGeom->setPixel(pixelPigment);
	// 			    curGeom->blinnPhong(ray, closestDistance);
	// 			    pixelPigment = curGeom->getPixel();

	// 			    setColor(&color, pixelPigment);
	// 			    img.pixel(i, j, color);
	// 			}
	// 		}

			/* Print unit test results */ 

			// for (int g = 0; g < allGeometry.size(); g++) {
			// 	allGeometry.at(g)->getPigmentA()->reset();
			// 	allGeometry.at(g)->getPigmentD()->reset();
			// 	allGeometry.at(g)->getPigmentS()->reset();
			// }
		// }
	// }


	return 0;
}
