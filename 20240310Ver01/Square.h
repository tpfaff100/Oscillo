#ifndef SQUARE_H
#define SQUARE_H

#include "Trig.h"

class Square : public Trig
{

public:
	float eval();
	float eval(float);
	float next(void);
};

#endif
