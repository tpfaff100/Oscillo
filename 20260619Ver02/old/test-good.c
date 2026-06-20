#include <stdio.h>
#include <math.h>

#define PI 3.1415926535

float f(double x){
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


int main(){
	float x;
	/**To plot in the rang of -6pi to 6pi **/
//	for (x=-6*PI; x<=6*PI; x=x+0.1) {
	for (x=0; x< PI*2; x+=.1) {
		printf("%f\t%f\t%f\n",x,f(x), sin(x));
	}
	return 0;
}

