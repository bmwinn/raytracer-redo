#ifndef _FINISH_H_
#define _FINISH_H_

#include <iostream>

using namespace std;

/* Contains BRDF details */
class Finish {
public:
	Finish();
	Finish(float amb, float diff, float spec, float refl, float refr, float rou, float io);
	void print();

public:
	float ambient, diffuse, specular, roughness, refract, reflect, ior;
};

#endif