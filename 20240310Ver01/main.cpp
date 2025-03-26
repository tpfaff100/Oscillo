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

/** Legend:
 **  A "Trig" object defines a sin or cos.  Not entirely efficient these could be done with integer-based lookup tables but currently are floating point 
 **  An "Oscill"ator object defines a quadrature oscillator.  It can generate a sin and cos waveform.
 **  A  "Bank" defines a collection of oscillators.  These can be plotted on top of each other or can be merged (added) together
 **
 **  Typically you want to create a bank of oscillators.  The oscillators are defined in a simple array.
 **  You need to clear the screen after each successive image is drawn.  After clearing screen...
 **  Then call the -->range() method repeatedly on the bank.  This will cycle through all of the oscillators and add them together
 **  Continue until the range exits.  You can also specify new range values 
 **  The bank also creates a "bitmap" which is drawn into and then displayed on the screen.
 **  
 **  pseudocode:  new Bank(oscillators); create phase shift from zero to PI*n.  Clear the bank and call  while(range()) until exit.
 **               Then call dump() to write the created bitmap (with the trig data) on the screen.
 **               adjust phase shift on any oscillators you like and start over (not reallocating anything of course).
 **		  See Test_Bank() for the C code that does all this.
 */

#include <iostream>

#include <unistd.h>
#include "Trig.h"
#include "Sin.h"
#include "Cos.h"
#include "Oscill.h"		/* Oscillator containing waveform type an her attributes */
#include "Bank.h"		/* Bank of oscillators we can select and iterate through */
#include "TextBitmap.h"		/* Get the list of colors we can use for drawing */
#include "Types.h"

#define ASPECT_X	4
#define ASPECT_Y	3	
#define DELAY		70000

void Test_Color() {
	float loopval;
	Oscill osc_ary[] = { Oscill(0.010f), Oscill(0.02f) };
	int osc_count = sizeof(osc_ary) / sizeof(osc_ary[0]);
	Bank *bank1 = new Bank(osc_ary, osc_count);
	bank1->setColorModulation(true, red, purple, .01);	/* optional, color modulation is off by default */

	osc_ary[0].setScale(50);
	osc_ary[0].swap();

	Color c1=green, c2=blue;

	while(1) {
		for (loopval = 0; loopval < PI/32; loopval+=.001) {
			while(bank1->range());          // do until specified range is exceeded in osc 0.
			bank1->setColorModulation(true, c1, c2, loopval);
			bank1->dump();
			usleep(DELAY);
			std::system("clear");
			bank1->clear();
		}
		for (loopval = PI/32; loopval > 0; loopval-= .001) {
			while(bank1->range());          // do until specified range is exceeded in osc 0.
			bank1->setColorModulation(true, c1, c2, loopval);
			bank1->dump();
			usleep(DELAY);
			std::system("clear");
			bank1->clear();
		}
	}

        delete bank1;
}



void Test_Invert_Axes() {
//	Oscill osc_ary[] = { Oscill(0.01f), Oscill(0.04f) };
//	Oscill osc_ary[] = { Oscill(0.00101f), Oscill(0.001f), Oscill(0.00102f) };
//	Oscill osc_ary[] = { Oscill(0.101f), Oscill(0.200f), Oscill(0.00400f) };
//	Oscill osc_ary[] = { Oscill(0.120f), Oscill(0.200f) };
//	Oscill osc_ary[] = { Oscill(0.030f), Oscill(0.050f) };
	Oscill osc_ary[] = { Oscill(0.00150f), Oscill(0.0025f) };
//	Oscill osc_ary[] = { Oscill(0.00150f), Oscill(0.003f) };
	int osc_count = sizeof(osc_ary) / sizeof(osc_ary[0]);
	Bank *bank1 = new Bank(osc_ary, osc_count);
        bank1->setColorModulation(true, white, red, .0015);       /* optional, color modulation is off by default */

	osc_ary[0].setScale(50);
	osc_ary[0].swap();


	osc_ary[0].setScale(70);
	osc_ary[1].setScale(20);
//	osc_ary[2].setScale(100);

//	for (int count = 0; count < PI*2; count++) {
		for (float ps = 0; ps <= PI*8; ps+= .01) {
			usleep(DELAY);
			std::system("clear");
			bank1->clear();

			while(bank1->range());		// do until specified range is exceeded in osc 0.
			bank1->dump();
		}
//	}

	delete bank1;
}

void Test_Bank() {
//	Oscill osc_ary[] = { Oscill(0.00101f), Oscill(0.001f) };
	Oscill osc_ary[] = { Oscill(0.00101f), Oscill(0.001f), Oscill(0.00401f) };
	int osc_count = sizeof(osc_ary) / sizeof(osc_ary[0]);
	Bank *bank1 = new Bank(osc_ary, osc_count);
	bank1->setColorModulation(true, green, blue, .2);	/* optional, color modulation is off by default */

	/* use one-shot oscillators (they stop after one cycle) */
	osc_ary[0].setContinous(ONESHOT);
	osc_ary[1].setContinous(ONESHOT);
	osc_ary[2].setContinous(ONESHOT);

	for (int count = 0; count < 2; count++) {
		for (float ps = 0; ps <= PI*32; ps+= .1) {
			usleep(DELAY);
//			std::system("clear");
			bank1->clear();

			while(bank1->range());		// do until specified range is exceeded in osc 0.
			bank1->dump();

			osc_ary[0].reset();
			osc_ary[0].setPhaseO1(ps);
			osc_ary[1].setPhaseO1(ps/2);
			osc_ary[2].setPhaseO1(ps/8);
		}
		osc_ary[0].swap();	// flip one of the oscillator's axes (i.e. sin becomes cos, cos becomes sin).
sleep(2);
	}

	delete bank1;
}

void Test_Oscillators() {
        int x,y;
        u1 surface[SCALE][SCALE];
        Oscill *o1 = new Oscill(0.00101f); /* create a quadrature  oscillator */
        Oscill *o2 = new Oscill(0.001f);

        std::system("clear");

        // ps = sin waveform phase shift.
        for (float ps = 0; ps <= PI*16; ps+= .01) {
                memset(surface, ' ', SCALE*SCALE);// clear the drawing surface
                usleep(DELAY);
                std::system("clear");


                // run one oscillator cycle, storying values in the (x,y) surface array.
                while (o1->range() ) {
                        o2->range();

                        int x = int(o1->chan1 + o2->chan1) / 2;
                        int y = int(o1->chan2 + o2->chan2) / 2;
                        surface[x][y] = '*';    // plot the circle
                };

                // draw the oscillator cycle data.
                for (int y = 0; y < SCALE; y++) {
                        for (int x=0; x < SCALE; x++) {
                                printf("%c", surface[x][y]);
                                printf("%c", surface[x][y]);
                        }
                        printf("\n");
                }

                o1->reset();
                o1->setPhaseO1(ps);
        }

        delete o2;
        delete o1;
}



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
//      Test_Oscillator();
//      Test_Oscillators();
//	Test_Bank();
//	Test_Invert_Axes();
	Test_Color();
}
