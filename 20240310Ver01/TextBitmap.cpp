#include <iostream>
#include "TextBitmap.h"


using namespace std;

TextBitmap::TextBitmap() {
	setColor(green);
}

void TextBitmap::clear(void) {
	memset(bmap, ' ', SCALE*SCALE);		// clear the drawing surface
};	

void TextBitmap::setColor(int color) {
	this->color = color;
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
	for (int y = 0; y < SCALE; y++) {
		for (int x=0; x < SCALE; x++) {
			u1 pixel = bmap[x][y];

			if (pixel== '*')
				color=green;
			else
				color=blue;

			if (color == green)
				printf("%s%c%c", TEXT_COLOR_GREEN, pixel, pixel);
			else
				printf("%s%c%c", TEXT_COLOR_BLUE, pixel, pixel);
		}
		printf("\n");
	}

};
