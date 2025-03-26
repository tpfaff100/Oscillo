#include <iostream>
#include <cmath>
#include "Square.h"


using namespace std;

/**
Let’s say that there is a function f(x) which is periodic with a period of 2*T and is already defined in the interval [-T,T].

Then the function should have the same value at: f(x), f(x+2T), f(x+4T), ….

i.e. f(x)=f(x+2T)=f(x+4T)=……. since period=2*T.

But I said that the function is defined only in the interval [-T,T]. So how is the computer supposed to calculate it’s value at x>T?
That’s easy. Since the value of the function at f(x+2T) is simply f(x), therefore we can generalize that whenever x>T: then,
f(x)=f(x-2T).  Note: We have to keep taking x back by 2T i.e (x-2T) until it lies  within [-T,T] where the function is well-defined.

Similarly what about the value of function at x less than (-T) cause the function is not defined for values less than (-T)?
Again, this time we use:f(x)=f(x+2T). Note: We keep translating x forward by 2T  i.e (x+2*T) until it lies  within [-T,T] where the function is well-defined.

Using the above two arguments we can create a function which will make any given function defined within [-T,T] and with a period 2*T a periodic function.
*/

float f(float x){
        if(x>=0 && x<PI) {
                return x;
        }
        else if(x>=PI && x<2*PI) {
                return 2*PI-x;
        }
        else if(x >= 2*PI) {
                return f(x-2*PI);
        }
        else if(x < 0) {
                return f(x+2*PI);
        }
        return 0.0f;
}


float triangle(float radians) {
        return f(radians*2)/4.0f;
}


float square(float radians) {
	if (triangle(radians) > .5) {
		return 1.0;
	}
	return -1.0;
}


float Square::eval() {
//	return sin(current+radians+phase);
	return triangle(current+radians+phase);
//	return 0.6*asin(sin(2 * (PI / 2.0f) * (current+radians+phase)));
};

float Square::eval(float radians) {
	return asin(sin(2 * (PI / 2.0f) * (radians)));
};

float Square::next() {
	current += incrate;
//printf("%f  %f\n", sin(current+radians+phase), asin(sin(2 * (PI / 2.0f) * (current+radians+phase))));
//	return triangle(current+radians+phase);
	return sin(current+radians+phase);
//	return square(current+radians+phase);
//	return 0.6*asin(sin(2 * (PI / 2.0f) * (current+radians+phase)));
};
