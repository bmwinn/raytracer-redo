#ifndef _POINT_H_
#define _POINT_H_

class Point {
public:
	Point();
	Point(float x, float y, float z);
	~Point();
	float distance(Point *other);

	void setX(float x);
	void setY(float y);
	void setZ(float z);

	float getX();
	float getY();
	float getZ();
private:
	float x, y, z;
};

#endif