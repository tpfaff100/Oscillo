#include <iostream>
#include <cmath>
#include "Sin.h"

using namespace std;

float Sin::eval(float radians) {
	return sin(radians);
}

float Sin::next() {
	current += incrate;
//printf("this = %lx, current = %f, incrate = %f\n", this, current, incrate);
	return sin( current + radians + phase);
}
