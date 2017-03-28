#ifndef _POINT_H_
#define _POINT_H_

class Point {
public:
	Point();
	Point(float x, float y, float z);
	~Point();
	float distance(Point *other);
	float x, y, z;
};

#endif