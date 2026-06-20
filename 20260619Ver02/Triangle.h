#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Trig.h"

class Triangle : public Trig
{

public:
	float eval();
	float eval(float);
	float next(void);

	float triangle(float radians); 

};

#endif
