#ifndef _PIGMENT_H_
#define _PIGMENT_H_

/* Used for rgb or rgbf colors */
class Pigment {
public:
	Pigment();
	Pigment(float r, float g, float b, float f);
	void Reset();
	float r, g, b, f;
};

#endif