#include <iostream>
#include <cmath>
#include "Triangle.h"

#include <numbers>

using namespace std;


float tri(float x) { 			// std::asin(std::sin(x)) creates a triangular zigzag
    // Dividing by (std::numbers::pi / 2.0) scales the output to fit the range [-1.0, 1.0]
    return (2.0 / std::numbers::pi) * std::asin(std::sin(x));
}

/*
float sawtooth(float x) {
    // Avoid division by zero when sin(x/2) is exactly 0
    double sin_half = std::sin(x / 2.0);
    if (std::abs(sin_half) < 1e-15) {
        return -1.0; // Reset point of the sawtooth
    }
    
    double cot = std::cos(x / 2.0) / sin_half;
    return -2.0 * std::atan(cot) / M_PI;
}
*/


float Triangle::triangle(float radians) {
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
	return tri(current+radians+phase);
//	return sawtooth(current+radians+phase);
}
