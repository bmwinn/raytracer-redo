// TODO
// rethink fileops?
#include "RayTrace.h"

int main(int argc, char *argv[]) {
	int width, height;
	string input, outTGA;
	string test;
	Light light;
	Camera camera;
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
	if (fileOps(argc, argv, &width, &height, &test, &allGeometry, &camera, &light)) {
		/* Otherwise, fileOps prints error message. Quit program. */
		return 1;
	}

	Image img(width, height);
	
	rayTrace(width, height, &camera, &light, &img, &allGeometry, test);
	
	img.WriteTga((char *)outTGA.c_str(), true);

	return 0;
}
