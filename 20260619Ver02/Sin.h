#ifndef SIN_H
#define SIN_H

#include "Trig.h"

class Sin : public Trig
{

public:
	float eval(float);
	float next(void);
};

#endif
