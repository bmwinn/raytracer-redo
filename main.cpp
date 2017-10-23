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

	// save name of input file
	input = argv[3];

	// save name of output directory
	outTGA = argv[4];
	outTGA += "/";

	// rename output .tga file; "input.pov" -> "input.tga"
	for (int i = 0; i < input.size(); i++) {
		if (input.at(i) == '.')
			i = input.size();
		else
			outTGA += input.at(i);
	}
	outTGA += ".tga";

	// Attempt to open .pov file, fill in variables, and create geometry
	if (fileOps(argc, argv, &width, &height, &test, &allGeometry, &camera, &light)) {
		// Otherwise, fileOps prints error message. Quit program.
		return 1;
	}

	// Create empty image of size width * height
	Image img(width, height);
	
	// loop through width * height pixels
	// for each pixel,
	//    fill in pixel with color of hit geometry
	//    (allows up to 5 bounces for refractive/reflective objects)
	renderLoop(width, height, &img, &allGeometry, camera, 5);
	
	// Write .tga file
	img.WriteTga((char *)outTGA.c_str(), true);

	return 0;
}
