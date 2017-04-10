#ifndef _FINISH_H_
#define _FINISH_H_

/* Contains BRDF details */
class Finish {
public:
	Finish();
	Finish(float ambient, float diffuse, float specular, float roughness);

	void setAmbient(float a);
	void setDiffuse(float d);
	void setSpecular(float s);
	void setRoughness(float r);

	float getAmbient();
	float getDiffuse();
	float getSpecular();
	float getRoughness();

private:
	// make public?
	float ambient, diffuse, specular, roughness;
};

#endif