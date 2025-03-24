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
/*
	switch(color)
	{
	    case black 	: std::cout << TEXT_COLOR_BLACK;	break;
	    case red 	: std::cout << TEXT_COLOR_RED;   	break;
	    case green 	: std::cout << TEXT_COLOR_GREEN;	break;
	    case yellow : std::cout << TEXT_COLOR_YELLOW;	break;
	    case blue 	: std::cout << TEXT_COLOR_BLUE;		break;
	    case purple : std::cout << TEXT_COLOR_PURPLE;	break;
	    case cyan 	: std::cout << TEXT_COLOR_CYAN;		break;
	    case white	: std::cout << TEXT_COLOR_WHITE;	break;
	    default	: std::cout << TEXT_COLOR_GREEN;	break;
	}
*/
	int currColor = color1;

	if (color_mod_enable == true) {
		for (int y = 0; y < SCALE; y++) {
			for (int x=0; x < SCALE; x++) {
				u1 pixel = bmap[x][y];

				if (pixel== '*')
					currColor=green;
				else
					currColor=cyan;

				if (currColor == green)
					printf("%s%c%c", TEXT_COLOR_GREEN, pixel, pixel);
				else
					printf("%s%c%c", TEXT_COLOR_BLUE, pixel, pixel);
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
