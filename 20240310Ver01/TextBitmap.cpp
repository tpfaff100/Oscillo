#include <iostream>
#include "TextBitmap.h"


using namespace std;

TextBitmap::TextBitmap() {
	setColor(false, green, blue);		// set colors but disable color modulation by default.
}

void TextBitmap::clear(void) {
	memset(bmap, ' ', SCALE*SCALE);		// clear the drawing surface
};	

void TextBitmap::setColor(bool color_mod_enable, Color color, Color altcolor) {
	this->color1 = color;
	this->color2 = altcolor;
	this->color_mod_enable = color_mod_enable;
}

void TextBitmap::dump(void) {
	int currColor = color1;

	if (color_mod_enable == true) {
		for (int y = 0; y < SCALE; y++) {
			for (int x=0; x < SCALE; x++) {
				u1 pixel = bmap[x][y];

				if (pixel== '*')
					currColor=color1;
				else
					currColor=color2;
				
				switch(currColor) {
					case black:	printf("  ");							break;
					case red: 	printf("%s%c%c", TEXT_COLOR_RED, pixel, pixel);			break;
					case green: 	printf("%s%c%c", TEXT_COLOR_GREEN, pixel, pixel);		break;
					case blue: 	printf("%s%c%c", TEXT_COLOR_BLUE, pixel, pixel);		break;
					case purple: 	printf("%s%c%c", TEXT_COLOR_PURPLE, pixel, pixel);		break;
					case yellow: 	printf("%s%c%c", TEXT_COLOR_YELLOW, pixel, pixel);		break;
					case cyan: 	printf("%s%c%c", TEXT_COLOR_CYAN, pixel, pixel);		break;
					case white: 	printf("%s%c%c", TEXT_COLOR_WHITE, pixel, pixel);		break;
					default: 	printf("%s%c%c", TEXT_COLOR_GREEN, pixel, pixel);		break;
				}
			}
			printf("\n");
		}
	}
	else {

                for (int y = 0; y < SCALE; y++) {
                        for (int x=0; x < SCALE; x++) {
				register int pixel = bmap[x][y];
				printf ("%c%c", pixel, pixel);
			}
			printf("\n");
		}
	}
};
