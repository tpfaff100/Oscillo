#ifndef TEXT_BITMAP_H 
#define TEXT_BITMAP_H

#include "Oscill.h"
#include "Types.h"

class TextBitmap {
public:
	u1 bmap[SCALE][SCALE];

	void clear(void);
	void dump(void);
};

#endif
