#ifndef _FINISH_H_
#define _FINISH_H_

#include <iostream>

using namespace std;

/* Contains BRDF details */
class Finish {
public:
	Finish();
	Finish(float ambient, float diffuse, float specular, float roughness);
	void print();

public:
	float ambient, diffuse, specular, roughness, refract, reflect, ior;
};

#endif