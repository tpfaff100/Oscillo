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

	color_mod_waveform = new Square();	// waveform used to implement color cycling.
	color_mod_waveform->setIncRate(.2);
	disable_color_mod = true;

	amplitude_waveform = new Square();
	amplitude_waveform->setIncRate(.01);

}

Bank::Bank(Oscill *ary, int size) {
	osc_ary = ary;
	osc_count = size;
	surface = new TextBitmap();

	color_mod_waveform = new Square();	// oscillator used to implement color cycling.
	color_mod_waveform->setIncRate(.02);
	disable_color_mod = true;
	
	amplitude_waveform = new Square();
	amplitude_waveform->setIncRate(.01);
}

Bank::~Bank() {
	if (surface != NULL)
		delete surface;
	if (color_mod_waveform != NULL)
		delete color_mod_waveform;
	if (amplitude_waveform != NULL)
		delete amplitude_waveform;
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
			if (inrange == false) {		// this should only happen once an animation frame ==> not wasting a lot of cycles here.
				osc_ary[count].setScale(SCALE*amplitude_waveform->next());	// tickle the amplitude waveform oscillator once every animation frame.
				osc_ary[count].reset();	
			}
		}

		x += int(osc_ary[count].chan1);
		y += int(osc_ary[count].chan2);
	}
	x = x / osc_count;
	y = y / osc_count;

//not really useful this scales from origin but left here just as an example of how to do this.
//	float scalar = amplitude_waveform->eval();// determine x/y scaling value from oscillator for the current aniimation fram for the current aniimation framee.
//	x = (int) ( (float) scalar * (float)x);
//	y = (int) ( (float) scalar * (float)y);

	color_mod_waveform->next();		// tickle the color modulation oscillator.
	if (disable_color_mod == false) {
		if (color_mod_waveform->next() > 0.0) 
			surface->bmap[x][y] = '.';    // write a 'pixel' to the offscreen bitmap.
		else
			surface->bmap[x][y] = '*';    // write a 'pixel' to the offscreen bitmap.

	} else {				// no color modulation so let's keep it simple!
		surface->bmap[x][y] = '*';	// colorless. Runs faster/cleaner w/ complex shapes.
	}
	return inrange;		// use the 0th oscillator's range to determine completion.
}

void Bank::clear(void) {
	surface->clear();
}
void Bank::dump(void) {
	surface->dump();
}

void Bank::setColorModulation(bool enable, Color color1, Color color2, float incrementRate) {
	surface->setColor(enable, color1, color2);
	color_mod_waveform->setIncRate(incrementRate);
	disable_color_mod = !enable;
}

Oscill *Bank::oscillatorAt(int index) {
	return osc_ary+index;
}

