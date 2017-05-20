#ifndef _PIGMENT_H_
#define _PIGMENT_H_

#include <iostream>

#include "Image.h"

using namespace std;

/* Used for rgb or rgbf colors */
class Pigment {
public:
	Pigment();
	Pigment(float r, float g, float b, float f = 1);
	void reset();
	void print();

	void operator+=(Pigment *other);
	void cap(); // added during blinn phong part 2, may be unnecessary to autoinclude within pigment functions
	void bigCap(color_t *color);

	void setColorT(color_t *color);
	
public:
	float r, g, b, f;
};

#endif