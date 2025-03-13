#include <iostream>
#include "TextBitmap.h"


using namespace std;


void TextBitmap::clear(void) {
	memset(bmap, ' ', SCALE*SCALE);		// clear the drawing surface
};	

void TextBitmap::dump(void) {
	for (int y = 0; y < SCALE; y++) {
		for (int x=0; x < SCALE; x++) {
			printf("%c", bmap[x][y]);
			printf("%c", bmap[x][y]);
		}
		printf("\n");
	}

};
