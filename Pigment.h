#ifndef _PIGMENT_H_
#define _PIGMENT_H_

/* Used for rgb or rgbf colors */
class Pigment {
public:
	Pigment();
	Pigment(float r, float g, float b, float f);
	void Reset();

	void setR(float r);
	void setG(float g);
	void setB(float b);
	void setF(float f);

	float getR();
	float getG();
	float getB();
	float getF();

private:
	float r, g, b, f;
};

#endif