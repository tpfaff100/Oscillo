#include <iostream>
#include <cmath>
#include "Square.h"

using namespace std;

float Square::eval(float radians) {
	return sin(radians);
};

float Square::next() {
	current += incrate;
	return sin( current + radians + phase);
};
