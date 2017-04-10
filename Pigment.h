#ifndef _PIGMENT_H_
#define _PIGMENT_H_

#include "Image.h"

/* Used for rgb or rgbf colors */
class Pigment {
public:
	Pigment();
	Pigment(float r, float g, float b, float f = 1);
	void reset();

	void operator+=(Pigment *other);
	void cap(); // added during blinn phong part 2, may be unnecessary to autoinclude within pigment functions
	void bigCap(color_t *color);

	void setR(float r);
	void setG(float g);
	void setB(float b);
	void setF(float f);
	void setColorT(color_t *color);

	float getR();
	float getG();
	float getB();
	float getF();

private:
	// make public
	float r, g, b, f;
};

#endif