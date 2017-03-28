#ifndef _FINISH_H_
#define _FINISH_H_

/* Contains BRDF details */
class Finish {
public:
	Finish();
	Finish(float ambient, float diffuse, float specular, float roughness);
	float ambient, diffuse, specular, roughness;
};

#endif