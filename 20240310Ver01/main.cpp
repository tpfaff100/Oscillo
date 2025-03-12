/** Oscillo - written March 8, 2025, mostly.  This program is designed to replace
 **           my 8-channel quadrature oscillator synthesizer/analog computer thing
 **           I built years ago.  It consisted of a bank of Burr Brown 4423 quadrature
 **           oscillators, a mixer, a frequency multiplier and opamps, etc.
 **            Was lots of fun as an interactive engine and I did many shows
 **            with it in the past but it's time to render the functionality into code
 **
 ** Thomas Poff  March 2025  Just make it should build on Linux, MacOS, Cygwin, etc
 **
 ** Requirements:  gcc, g++, make utility.  This module is mostly C code the rest is C++
 */

#include <iostream>
#include <unistd.h>
#include "Trig.h"
#include "Sin.h"
#include "Cos.h"
#include "Oscill.h"		/* Oscillator containing waveform type an her attributes */
#include "Bank.h"		/* Bank of oscillators we can select and iterate through */

#define SCALE		80
#define ASPECT_X	4
#define ASPECT_Y	3	
#define DELAY		50000

typedef unsigned char u1;




/* Draws a giant circle, animation */
/* This is the object-based version of the first function I wrote, Test_Waveform_Anim */
/* It adds real use of quadrature oscillation in a single dual-oscillator. */
/* This is essentially an emlulation of one old Burr Brown 4423 analog quadrature oscillator chip */
/* Look it up and you'll be surprised... it's a nice chip.  Requires +12/-12V and
   dual-ganged potentiometers.  The latter are unavailable now in the right values
   so I thought for years I should write this code, now that computers are fast enough to emulate! */
void Test_Oscillator() {
	int x,y;
	u1 surface[SCALE][SCALE];
	Oscill *o = new Oscill(0.01f);	/* create a quadrature  oscillator */

	std::system("clear");

	// ps = sin waveform phase shift.
	for (float ps = 0; ps <= PI*2; ps+= .01) {
		memset(surface, ' ', SCALE*SCALE);// clear the drawing surface
		usleep(DELAY);
		std::system("clear");

		
		// run one oscillator cycle, storying values in the (x,y) surface array.
		while (o->range() ) {
			surface[int(o->chan1)][int(o->chan2)] = '*';	// plot the circle
		};
		// draw the oscillator cycle data.
		for (int y = 0; y < SCALE; y++) {
			for (int x=0; x < SCALE; x++) {
				printf("%c", surface[x][y]);
				printf("%c", surface[x][y]);
			}
			printf("\n");
		}

		o->reset();
		o->setPhaseO1(ps);
	}

	delete o;
}



/* Draw a giant circle and animate lissajous pattern */
/* This is a nearly straight-C version I prototyped this on the night of March 8 2025.  Fun! */
void Test_Waveform_Anim() {
	int x,y;
        float val = PI;
        Sin *s = new Sin();
	Cos *c = new Cos();

	u1 surface[SCALE][SCALE];

	do {

		for (float ps=0; ps < 6.28; ps += .1) {
			usleep(DELAY);
			std::system("clear");
			memset(surface, ' ', SCALE*SCALE);// clear the drawing surface

			for (float range=0; range < PI*2; range += .01) {
				x = (int) (s->eval(range*ps) * (float) SCALE);
				y = (int) (c->eval(range) * (float) SCALE);

				x = SCALE/2 + x / 2;
				y = SCALE/2 + y / 2;

//		                printf("%d\t%d\n", x,y);
				surface[x][y] = '*';	// plot the circle
			}

			for (y = 0; y < SCALE; y++) {
				for (x=0; x < SCALE; x++) {
					printf("%c", surface[x][y]);
					printf("%c", surface[x][y]);
				}
				printf("\n");
			}
		}


		for (float ps=4; ps >= 1; ps -= .1) {
			usleep(DELAY);
			std::system("clear");
			memset(surface, ' ', SCALE*SCALE);// clear the drawing surface

			for (float range=0; range < PI*2; range += .005) {
				x = (int) (s->eval(range*ps) * (float) SCALE);
				y = (int) (c->eval(range) * (float) SCALE);

				x = SCALE/2 + x / 2;
				y = SCALE/2 + y / 2;

		//                printf("%d\t%d\n", x,y);
				surface[x][y] = '*';	// plot the circle
			}

			for (y = 0; y < SCALE; y++) {
				for (x=0; x < SCALE; x++) {
					printf("%c", surface[x][y]);
					printf("%c", surface[x][y]);
				}
				printf("\n");
			}
		}

	} while(1);

	delete c;
	delete s;
}


int main(void) {
//	Test_Waveform_Anim();
	Test_Oscillator();
	
}
