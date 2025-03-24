/** 
 **
 ** A bank of oscillators is a collection of quadratture oscillators that can be mixed together to 
 ** generate output on the x+y axis for one channel or mix of signals.  In a real laser 
 ** imagine system, this could be a group of x/y galvonometer scanners that project a laser
 ** onto a wall or screen.  A second laser signal/mix would go into another bank. 
 **
 */

#include <iostream>
#include <vector>
#include <cmath>
#include "Bank.h"
#include "Oscill.h"

using namespace std;

Bank::Bank() {
	osc_ary = NULL;
	osc_count = 0;
	surface = NULL;

	color_osc = new Square();	// oscillator used to implement color cycling.
	color_osc->setIncRate(.2);
}

Bank::Bank(Oscill *ary, int size) {
	osc_ary = ary;
	osc_count = size;
	surface = new TextBitmap();

	color_osc = new Square();	// oscillator used to implement color cycling.
	color_osc->setIncRate(.2);
}

Bank::~Bank() {
	if (surface != NULL)
		delete surface;
	if (color_osc != NULL)
		delete color_osc;
}



/** call this until receiving a FALSE condition.  FALSE indicates the end of a cycle
 ** based on the 0th oscillator's state only.  
 */
bool Bank::range(void) {
	bool inrange = false;
	int x = 0, y = 0;

	for (int count = osc_count-1; count >= 0; count--) {
		inrange = osc_ary[count].range();	// iterate quadrature oscillators.

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

	float foo = color_osc->next();
	if (color_osc->next() > 0.0) 
		surface->bmap[x][y] = '.';    // write a 'pixel' to the offscreen bitmap.
	else
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

