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

	void setAmbient(float a);
	void setDiffuse(float d);
	void setSpecular(float s);
	void setRoughness(float r);
	void setRefract(float r);
	void setReflect(float r);
	void setIor(float i);

	float getAmbient();
	float getDiffuse();
	float getSpecular();
	float getRoughness();
	float getRefract();
	float getReflect();
	float getIor();

private:
	// make public?
	float ambient, diffuse, specular, roughness, refract, reflect, ior;
};

#endif