#include "Geometry.h"

Geometry::Geometry() {
	normal = Vector();
	pigment = Pigment();
	finish = Finish();
}

void Geometry::SetNormal(Vector *other) {
	normal.x = other->x;
	normal.y = other->y;
	normal.z = other->z;
}

void Geometry::SetPigment(Pigment *other) {
	pigment.r = other->r;
	pigment.g = other->g;
	pigment.b = other->b;
	pigment.f = other->f;
}

void Geometry::SetFinish(Finish *other) {
	finish.ambient = other->ambient;
	finish.diffuse = other->diffuse;
	finish.specular = other->specular;
	finish.roughness = other->roughness;
}

/* Virtual function, should not be called */
void Geometry::Print() {
	cout << "This is a Geometry object." << endl;
}

/* Virtual function, should not be called */
float Geometry::Intersect(Ray *ray, Camera *camera) {
	cout << "Geometry object intersect." << endl;
	return 10000;
}
