#include <iostream>
#include <cmath>
#include "Triangle.h"

#include <numbers>

using namespace std;


float tri(float x) { 			// std::asin(std::sin(x)) creates a triangular zigzag
    // Dividing by (std::numbers::pi / 2.0) scales the output to fit the range [-1.0, 1.0]
    return (2.0 / std::numbers::pi) * std::asin(std::sin(x));
}



float Triangle::triangle(float radians) {
//        return f_tri(radians*2)/4.0f;
	return triangle(radians*2)/4.0f;
}


float Triangle::eval() {
	return triangle(current+radians+phase);
}

float Triangle::eval(float radians) {
	return asin(sin(2 * (PI / 2.0f) * (radians)));
}

float Triangle::next() {
	current += incrate;
//	return sin(current+radians+phase);
	return tri(current+radians+phase);
}
