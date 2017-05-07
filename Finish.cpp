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

void Finish::setAmbient(float a) { ambient = a; }
void Finish::setDiffuse(float d) { diffuse = d; }
void Finish::setSpecular(float s) { specular = s; }
void Finish::setRoughness(float r) { roughness = r; }
void Finish::setRefract(float r) { refract = r; }
void Finish::setReflect(float r) { reflect = r; }
void Finish::setIor(float i) { ior = i; }

float Finish::getAmbient() { return ambient; }
float Finish::getDiffuse() { return diffuse; }
float Finish::getSpecular() { return specular; }
float Finish::getRoughness() { return roughness; }
float Finish::getRefract() { return refract; }
float Finish::getReflect() { return reflect; }
float Finish::getIor() { return ior; }