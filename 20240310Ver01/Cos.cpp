#include <iostream>
#include <cmath>
#include "Cos.h"

using namespace std;

float Cos::eval(float radians) {
	return cos(radians);
};

float Cos::next() {
	current += incrate;
        return cos( current + radians + phase);
};      

