#ifndef _UNIT_TEST_H_
#define _UNIT_TEST_H_

/* Print unit test information for spheres.pov and planes.pov */
void printUnitTest(string *test, int i, int j, float closestDistance, Ray *ray, Pigment *pixelPigment, color_t *color) {
	if ((!test->compare("planes.pov") && ((i == 320 && j == 50) || (i == 50 && j == 240) || (i == 590 && j == 240))) || 
		(!test->compare("spheres.pov") && ((i == 320 && j == 239) || (i == 360 && j == 219) || (i == 230 && j == 239) || (i == 120 && j == 349) || (i == 490 && j == 119)))) {
		cout << "Pixel: [" << i << ", " << j << "]  Ray: {" << ray->getStart()->getX() << " " << ray->getStart()->getY() << " " << ray->getStart()->getZ() << "}";
		cout << " -> {" << ray->getDirection()->getX() << " " << ray->getDirection()->getY() << " " << ray->getDirection()->getZ() << "}";
		
		if (closestDistance == 10000)
			cout << "\tno hit       no hit" << endl;
		else {
			cout << "\tt = " << closestDistance;

			if (!test->compare("spheres.pov"))
				cout << "  Color: (" << (int) color->r << " " << (int) color->g << " " << (int) color->b << ")" << endl;
			else
				cout << "  Color: (" << pixelPigment->getR() << " " << pixelPigment->getG() << " " << pixelPigment->getB() << ")" << endl;
		}
	}
}

void printUnitTest2(string *test, int i, int j, int curGeom, float closestDistance, Ray *ray, Geometry *geometry, Light *light, Camera *camera) {
	if (!test->compare("simple.pov") && ((i == 420 && j == 130) || (i == 120 && j == 120) || (i == 295 && j == 265))) {
		if (i == 420 && j == 130)
			cout << "Shadow" << endl;
		else if (i == 120 && j == 120)
			cout << "Diffuse plane" << endl;
		else
			cout << "Specular highlight on sphere" << endl;

		cout << "Pixel: [" << i << ", " << j << "] Ray: {" << ray->getStart()->getX() << " " << ray->getStart()->getY() << " " << ray->getStart()->getZ() << "}";
		cout << " -> {" << ray->getDirection()->getX() << " " << ray->getDirection()->getY() << " " << ray->getDirection()->getZ() << "}";

		if (closestDistance < 0)
			cout << "\tnot hit\tno hit" << endl;
		else {
			cout << "\tT=" << closestDistance << endl;
		}

		cout << "Ambient: (" << geometry->pigmentA.getR() * 255 << ", " << geometry->pigmentA.getG() * 255 << ", " << geometry->pigmentA.getB() * 255 << ") ";
		cout << "Diffuse: (" << geometry->pigmentD.getR() * 255 << ", " << geometry->pigmentD.getG() * 255 << ", " << geometry->pigmentD.getB() * 255 << ") ";
		cout << "Specular: (" << geometry->pigmentS.getR() * 255 << ", " << geometry->pigmentS.getG() * 255 << ", " << geometry->pigmentS.getB() * 255 << ")" << endl;
		// cout << "Feeler: {" << geometry->feeler.direction.x << " " << geometry->feeler.direction.y << " " << geometry->feeler.direction.z << "}" << endl;
		cout << endl;
	}
}


#endif