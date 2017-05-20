#include "Finish.h"

Finish::Finish() {
	ambient = diffuse = specular = roughness = 0;
}

Finish::Finish(float ambient, float diffuse, float specular, float roughness) {
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->roughness = roughness;
}

void Finish::print() {
	std::cout << "finish a " << ambient << " d " << diffuse << " s " << specular;
	cout << " rou " << roughness << endl;
}
