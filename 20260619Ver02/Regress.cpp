#include <iostream>
#include <string>
#include <vector>

#include <unistd.h>
#include "Regress.h"
#include "Trig.h"
#include "Sin.h"
#include "Cos.h"
#include "OscillVector.h"
#include "Oscill.h"		/* Oscillator containing waveform type an her attributes */
#include "Bank.h"		/* Bank of oscillators we can select and iterate through */
#include "Sprite.h"
#include "Preset.h"
#include "Types.h"

#define ASPECT_X	4
#define ASPECT_Y	3	
#define DELAY		70000



/* This demonstrates two presets with two completely different waveform templates, loaded from disk.
 * Amazing.  We use two presets but only one framebuffer, fooling the -iterate: function to fool
 * preset two to add preset one's pattern into its own framebuffer, rendering two trigonemtric
 * two-dimensional functions at once.
 *
 * This is finally something better than what I used to do with my very excellent waveform generator 
 * that I wrote in 1990 on my 80286 PC, then again on Windows CE around Y2K.  Very nice demo!
 *
 * Imagine, two files, Time.prs and Anim.prs, rendered iteratively at the same time in real time
 * using Trig.  It's akin to listening to two radio stations at the same time!
 *
 * Or, to put it simply, very much like a 1980s-era analog computer based laser imaging system!
 * And we only needed 2+gigahertz processors to kind of do it!  Yay!
 *
 * TCP, 202606.19
 *
 */
void Regress::Test_Presets() {
	Preset *pr1 = new Preset("presets/Time.prs");
	Preset *pr2 = new Preset("presets/Anim.prs");
	Preset *pr3 = new Preset("presets/Animflower.prs");
	while( !pr2->iterate(pr1) ) {
		pr3->iterate(pr1);
		pr1->iterate(NULL);
		pr1->clear();
		pr1->sleep();
		std::system("clear");   // clear the screen.

	}
	delete pr3;
	delete pr2;
	delete pr1;
}

void Regress::Test_Preset() {
	Preset *pr1 = new Preset("presets/Time.prs");
	pr1->run();
	delete pr1;
}

void Regress::Test_Sprite() {
	std::string sFilename = "anims/globe.vt";	//23
//	std::string sFilename = "anims/prey.vt";		//20
//	std::string sFilename = "anims/flatmap.vt";	//21
//	std::string sFilename = "anims/sship.vt";	//16
//	std::string sFilename = "anims/movglobe.vt";	//16

        OscillVector osc_vec;
        osc_vec.push_back( Oscill(0.01f) );
	Bank *bank1 = new Bank(osc_vec);

	Sprite *sprite = new Sprite(sFilename, 23);
/*
 * If you want to avoid using the Bank object with oscillators you can do this instead: *
	for (int count = 0; count < 1024; count++) {
		std::string frame = sprite->next();
		usleep(DELAY);
		std::cout << frame;
	}
*/
	bank1->setSprite(sprite);	// attach the animation to the oscillator bank.

	while(bank1->range(NULL)) {
		bank1->dump();		// iterate and draw waveforms and animation.
		usleep(DELAY);
		std::system("clear");
		bank1->clear();
	}

	delete sprite;
	delete bank1;
}

void Regress::Test_Color() {
	float loopval;
//	Oscill osc_ary[] = { Oscill(0.010f), Oscill(0.02f) };
//	Oscill osc_ary[] = { Oscill(0.01f), Oscill(0.02f), Oscill(0.0201f), Oscill(0.0202f) };	// Breathe


        OscillVector osc_vec;
        osc_vec.push_back( Oscill(0.01f) );
        osc_vec.push_back( Oscill(0.02f) );
        osc_vec.push_back( Oscill(0.0201f) );
        osc_vec.push_back( Oscill(0.0202f) );
        Bank *bank1 = new Bank(osc_vec);

	bank1->setColorModulation(true, red, purple, .01);	/* optional, color modulation is off by default */
	bank1->setAmplitudeModulation(true);

	osc_vec.at(0).setScale(50);
	osc_vec.at(0).swap();

	Color c1=green, c2=blue;

	while(1) {
		for (loopval = 0; loopval < PI/32; loopval+=.001) {
			while(bank1->range(NULL));          // do until specified range is exceeded in osc 0.
			bank1->setColorModulation(true, c1, c2, loopval); // continuously changing color mod osc phase!
			bank1->dump();
			usleep(DELAY);
//			std::system("clear");
			bank1->clear();
		}
		for (loopval = PI/32; loopval > 0; loopval-= .001) {
			while(bank1->range(NULL));          // do until specified range is exceeded in osc 0.
			bank1->setColorModulation(true, c1, c2, loopval);
			bank1->dump();
			usleep(DELAY);
			std::system("clear");
			bank1->clear();
		}
	}

        delete bank1;
}



void Regress::Test_Invert_Axes() {
//	Oscill osc_ary[] = { Oscill(0.01f), Oscill(0.04f) };
//	Oscill osc_ary[] = { Oscill(0.00101f), Oscill(0.001f), Oscill(0.00102f) };
//	Oscill osc_ary[] = { Oscill(0.101f), Oscill(0.200f), Oscill(0.00400f) };
//	Oscill osc_ary[] = { Oscill(0.120f), Oscill(0.200f) };
//	Oscill osc_ary[] = { Oscill(0.030f), Oscill(0.050f) };
	Oscill osc_ary[] = { Oscill(0.00150f), Oscill(0.0025f) };
//	Oscill osc_ary[] = { Oscill(0.00150f), Oscill(0.0025f), Oscill(0.00025f) };
//	Oscill osc_ary[] = { Oscill(0.00150f), Oscill(0.003f) };


        OscillVector osc_vec;
	osc_vec.push_back( Oscill(0.00150f) );
	osc_vec.push_back( Oscill(0.00250f) );

        Bank *bank1 = new Bank(osc_vec);
        bank1->setColorModulation(true, white, red, .0015);       /* optional, color modulation is off by default */
//	bank1->setAmplitudeModulation(true);

	osc_vec.at(0).setScale(50);
	osc_vec.at(0).swap();

	osc_vec.at(0).setScale(70);
	osc_vec.at(1).setScale(20);
//	osc_vec.at(2).setScale(50);

//	osc_vec.at(2).setRate(.0005);

	for (float ps = 0; ps <= PI*8; ps+= .01) {
		usleep(DELAY);
		std::system("clear");
		bank1->clear();

		while(bank1->range(NULL));		// do until specified range is exceeded in osc 0.
		bank1->dump();
	}

	delete bank1;
}


void Regress::Test_Bank() {
	OscillVector osc_vec;
	Oscill a(0.00101f);
	Oscill b(0.001f);
	Oscill c(0.00401f);
//printf("%lx %lx %lx\n", &a, &b, &c);
	osc_vec.push_back( a );
	osc_vec.push_back( b );
	osc_vec.push_back( c );	// alt test - remove this line.

//printf("%lx %lx %lx\n", &osc_vec.at(0), &osc_vec.at(1), &osc_vec.at(2));

	Bank *bank1 = new Bank(osc_vec);
	bank1->setColorModulation(true, green, blue, .1);	/* optional, color modulation is off by default */

	/* use one-shot oscillators (they stop after one cycle) */
	for (Oscill o : osc_vec) {
		o.setContinuous(ONESHOT);
	}

	for (int count = 0; count < 2; count++) {
		for (float ps = 0; ps <= PI*32; ps+= .1) {
			usleep(DELAY);
			std::system("clear");
			bank1->clear();

			while(bank1->range(NULL));		// do until specified range is exceeded in osc 0.
			bank1->dump();
			osc_vec.at(0).reset();
			osc_vec.at(0).setPhaseO1(ps);
			osc_vec.at(1).setPhaseO1(ps/2);
			osc_vec.at(2).setPhaseO1(ps/8);

		}
		osc_vec.at(0).swap();	// flip one of the oscillator's axes (i.e. sin becomes cos, cos becomes sin).
sleep(2);
	}

	delete bank1;
}

void Regress::Test_Oscillators() {
        int x,y;
        u1 surface[SCALE][SCALE];
        Oscill *o1 = new Oscill(0.00101f); /* create a quadrature oscillator */
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
void Regress::Test_Oscillator() {
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
void Regress::Test_Waveform_Anim() {
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




void Regress::Test_Regression_Suite(int n) {

	switch (n) {
		case Test_1_Waveform_Anim:
			Test_Waveform_Anim();
			break;
		case Test_2_Oscillator_One:
			Test_Oscillator();
			break;
		case Test_3_Oscillators_Multi:
			Test_Oscillators();
			break;
		case Test_4_Bank_of_Oscillators:
			Test_Bank();
			break;
		case Test_5_Invert_Axes:
			Test_Invert_Axes();
			break;
		case Test_6_Colors:
			Test_Color();
			break;
		case Test_7_Sprite:
			Test_Sprite();
			break;
		case Test_8_Preset:
			Test_Preset();
			break;
		case Test_9_Presets_Multi:
			Test_Presets();
			break;
		case None:
			std::cout << "There is no 'None' test!\n\n";
			exit(0);
		default:
			break;
	}
}


