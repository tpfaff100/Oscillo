#include <iostream>
#include <cmath>
#include "Square.h"


using namespace std;

float Square::eval() {
	return sin(current+radians+phase);
//	return 0.6*asin(sin(2 * (PI / 2.0f) * (current+radians+phase)));
};

float Square::eval(float radians) {
	return asin(sin(2 * (PI / 2.0f) * (radians)));
};

float Square::next() {
	current += incrate;
//printf("%f  %f\n", sin(current+radians+phase), asin(sin(2 * (PI / 2.0f) * (current+radians+phase))));
	return sin(current+radians+phase);
//	return 0.6*asin(sin(2 * (PI / 2.0f) * (current+radians+phase)));
};
