#include <iostream>
#include <unistd.h>
#include "Trig.h"
#include "Sin.h"
#include "Cos.h"

#define SCALE		80
#define ASPECT_X	4
#define ASPECT_Y	3	
#define DELAY		50000

typedef unsigned char u1;

int main(void) {
	int x,y;
        float val = PI;
        Sin *s = new Sin();
	Cos *c = new Cos();

	u1 surface[SCALE][SCALE];

//	unsigned char *surface = new unsigned char[80 * 80];

	do {

	for (float ps=1; ps < 4; ps += .1) {
		usleep(DELAY);
		std::system("clear");
		memset(surface, ' ', SCALE*SCALE);// clear the drawing surface

		for (float range=0; range < PI*2; range += .01) {
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
