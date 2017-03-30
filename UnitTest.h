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
				cout << "  Color: (" << pixelPigment->r << " " << pixelPigment->g << " " << pixelPigment->b << ")" << endl;
		}
	}
}

#endif