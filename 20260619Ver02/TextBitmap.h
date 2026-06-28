#ifndef TEXT_BITMAP_H 
#define TEXT_BITMAP_H

#include "Oscill.h"
#include "Types.h"

#pragma once
#include <array>
#include <cstdint>              // for uint8_t on linux

#define TEXT_COLOR_LEN		10

#define TEXT_COLOR_BLACK	"\e[0;30m"
#define TEXT_COLOR_RED		"\e[0;31m"
#define TEXT_COLOR_GREEN	"\e[0;32m" 
#define TEXT_COLOR_YELLOW	"\e[0;33m"
#define TEXT_COLOR_BLUE		"\e[0;34m" 
#define TEXT_COLOR_PURPLE	"\e[0;35m" 
#define TEXT_COLOR_CYAN		"\e[0;36m" 
#define TEXT_COLOR_WHITE	"\e[0;37m" 


enum Color { black, red, green, yellow, blue, purple, cyan, white };
 

class TextBitmap {
public:
	
	static inline std::array<uint8_t, SCALE*SCALE> bmap_buf;


	// treat bmap_buf as a 2D array by returning ref to specific element
	uint8_t& get_element(size_t row, size_t col) {
		return bmap_buf[row * SCALE + col];
	}
	
	// const overload for safe read-only.
	const uint8_t& get_element(size_t row, size_t col) const {
		return bmap_buf[row * SCALE + col];
	}

//	u1 bmap[SCALE][SCALE];
	int color1, color2;
	bool color_mod_enable;

	TextBitmap();
	void clear(void);
	void setColor(bool color_mod_enable, Color color, Color altcolor);
	void dump(void);
};

#endif
