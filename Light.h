#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Point.h"
#include "Pigment.h"

#include <iostream>

using namespace std;

/* Contains Light location "center" and Pigment value */
class Light {
public:
	Light();
	Light(Point center, Pigment pigment);
	void Print();
	Point center;
	Pigment pigment;
};

#endif