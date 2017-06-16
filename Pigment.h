#ifndef _PIGMENT_H_
#define _PIGMENT_H_

#include <iostream>

#include "Image.h"

using namespace std;

/* Used for rgb or rgbf colors */
class Pigment {
public:
	Pigment();
	Pigment(float r, float g, float b, float f = 0);
	void reset();
	void print();
	void cap();

	void operator+=(Pigment other);
	Pigment operator*(float scalar);
	Pigment operator+(Pigment other);
	
public:
	float r, g, b, f;
};

#endif