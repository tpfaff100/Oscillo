#include <iostream>
#include <cmath>
#include "Sin.h"

using namespace std;

float Sin::eval(float radians) {
	return sin(radians);
};

float Sin::next() {
	current += incrate;
	return sin( current + radians + phase);
};
