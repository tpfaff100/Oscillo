#include <iostream>
#include <vector>
#include <cmath>
#include "Bank.h"
#include "Oscill.h"

using namespace std;

/** Does nothing for now.  Not a complete bank config!  */
Bank::Bank() {
	osc_ary = NULL;
	osc_count = 0;
	surface = NULL;
}

Bank::Bank(Oscill *ary, int size) {
	osc_ary = ary;
	osc_count = size;
	surface = new TextBitmap();
}

Bank::~Bank() {
	if (surface != NULL)
		delete surface;
}



/** call this until receiving a FALSE condition.  FALSE indicates the end of a cycle
 ** based on the 0th oscillator's state only.  
 */
bool Bank::range(void) {
	bool inrange = false;
	int x = 0, y = 0;

	for (int count = osc_count-1; count >= 0; count--) {
		inrange = osc_ary[count].range();

		// if an oscillator is in "one-shot" mode it stops oscillating after it completes its cycle/range.
		if (osc_ary[count].continuous == CONTINUOUS)
		{
			if (inrange == false)
				osc_ary[count].reset();
		}

		x += int(osc_ary[count].chan1);
		y += int(osc_ary[count].chan2);
	}
	x = x / osc_count;
	y = y / osc_count;
	surface->bmap[x][y] = '*';    // write a 'pixel' to the offscreen bitmap.

        return inrange;		// use the 0th oscillator's range to determine completion.
}

void Bank::clear(void) {
	surface->clear();
}
void Bank::dump(void) {
	surface->dump();
}

void Bank::setColor(int color) {
	surface->setColor(color);
}

Oscill *Bank::oscillatorAt(int index) {
	return osc_ary+index;
}

