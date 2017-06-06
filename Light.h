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
	void print();

	void setCenter(Point c);
	void setPigment(Pigment p);

	Point getCenter();
	Pigment getPigment();

private:
	Point center;
	Pigment pigment;
};

#endif