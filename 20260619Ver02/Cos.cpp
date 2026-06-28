#include <iostream>
#include <cmath>
#include "Cos.h"
#include "costable_0_0001.h"


using namespace std;


#define CONST_PI  3.14159265358979323846264338327950288419716939937510
#define CONST_2PI 6.28318530717958623199592693708837032318115234375000

#define modd(x, y) ((x) - (int)((x) / (y)) * (y))
#define lerp(w, v1, v2) ((1.0 - (w)) * (v1) + (w) * (v2))

double absd(double a) { *((unsigned long *)&a) &= ~(1UL << 63); return a; }

inline double cos_table_0_0001(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    return costable_0_0001[(int)(x * 10000 + 0.5)];
}



inline double cos_table_0_0001_LERP(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    double i = x * 10000.0;
    int index = (int)i;
    return lerp(i - index,                  /* weight      */
                costable_0_0001[index],     /* lower value */
                costable_0_0001[index + 1]  /* upper value */
                );
}




float Cos::eval(float radians) {
//	return cos_table_0_0001(radians);
	return cos(radians);
}

float Cos::next() {
	current += incrate;
        return cos( current + radians + phase);
}      

