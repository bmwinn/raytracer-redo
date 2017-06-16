#include "Finish.h"

Finish::Finish() {
	ambient = diffuse = specular = 0;
	reflect = refract = 0;
	ior = 1;
	roughness = 0.5;
}

Finish::Finish(float amb, float diff, float spec, float refl, float refr, float rou, float io) {
	ambient = amb;
	diffuse = diff;
	specular = spec;
	reflect = refl;
	refract = refr;
	roughness = rou;
	ior = io;
}

void Finish::print() {
	std::cout << "finish a " << ambient << " d " << diffuse << " s " << specular;
	cout << " rou " << roughness << " refr " << refract << " refl " << reflect;
	cout << " ior " << ior << endl;
}
