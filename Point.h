#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>

using namespace std;

class Point {
public:
	Point();
	Point(float x, float y, float z);
	~Point();
	float distance(Point *other);
	void print();

	void setX(float x);
	void setY(float y);
	void setZ(float z);

	float getX();
	float getY();
	float getZ();
	
private:
	// make public
	float x, y, z;
};

#endif