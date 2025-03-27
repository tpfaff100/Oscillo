/** 
 **
 ** A bank of oscillators is a collection of quadratture oscillators that can be mixed together to 
 ** generate output on the x+y axis for one channel or mix of signals.  In a real laser 
 ** imagine system, this could be a group of x/y galvonometer scanners that project a laser
 ** onto a wall or screen.  A second laser signal/mix would go into another bank. 
 **
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdio.h>
#include "Bank.h"
#include "Oscill.h"

using namespace std;

Bank::Bank() {
	osc_ary = NULL;
	osc_count = 0;
	surface = NULL;
	sprite = NULL;

	color_mod_waveform = new Triangle();	// waveform used to implement color cycling.
	color_mod_waveform->setIncRate(.2);
	disable_color_mod = true;

	amplitude_waveform = new Triangle();
	amplitude_waveform->setIncRate(.01);
	disable_amplitude = true;

}

Bank::Bank(Oscill *ary, int size) {
	osc_ary = ary;
	osc_count = size;
	surface = new TextBitmap();
	sprite = NULL;

	color_mod_waveform = new Triangle();	// oscillator used to implement color cycling.
	color_mod_waveform->setIncRate(.02);
	disable_color_mod = true;
	
	amplitude_waveform = new Triangle();
	amplitude_waveform->setIncRate(.01);
	disable_amplitude = true;
}

Bank::~Bank() {
	if (surface != NULL)
		delete surface;
	if (color_mod_waveform != NULL)
		delete color_mod_waveform;
	if (amplitude_waveform != NULL)
		delete amplitude_waveform;
}

#define BX	20

// draw a 1980s vt100 animation sprite frame into the text framebuffer.
void Bank::renderSpriteOffscreen(Sprite *sprite) {
        if (sprite != NULL) {
                const char *frame = sprite->next().c_str();     // well, this is a reach...
                int height = sprite->frame_height;
                int bx = BX, by = 40;
                char pixel = ' ';

//              cout << frame;		// test here.

                // xfer the antiquated vt100 frame to our super high-tech framebuffer!
                for (int row = 0; row < height; row++) {
                        do {
                                pixel = *frame++;

                                surface->bmap[bx++][by] = pixel;
//printf("%d  %d  %c\n", bx, by, pixel);
                        } while( pixel != '\n');

			surface->bmap[bx-1][by] = ' ';
                        bx = BX;
                        by++;
                }

        }
}


/** call this until receiving a FALSE condition.  FALSE indicates the end of a cycle
 ** based on the 0th oscillator's state only.  
 */
bool Bank::range(void) {
	bool inrange = false;
	int x = 0, y = 0;

	if (sprite != NULL) 
		renderSpriteOffscreen(this->sprite);

	for (int count = osc_count-1; count >= 0; count--) {
		inrange = osc_ary[count].range();	// iterate quadrature oscillators.

		// if an oscillator is in "one-shot" mode it stops oscillating after it completes its cycle/range.
		if (osc_ary[count].continuous == CONTINUOUS)
		{
			if (inrange == false) {		// this should only happen once an animation frame ==> not wasting a lot of cycles here.
				if (!disable_amplitude) { 	// tickle the amplitude waveform oscillator once every animation frame.
					osc_ary[count].setScale(SCALE*amplitude_waveform->next());	
				}
//check
//printf("%f\n", SCALE*amplitude_waveform->next());
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

void Bank::setSprite(Sprite *sprite) {
	this->sprite = sprite;
}

void Bank::setColorModulation(bool enable, Color color1, Color color2, float incrementRate) {
	surface->setColor(enable, color1, color2);
	color_mod_waveform->setIncRate(incrementRate);
	disable_color_mod = !enable;
}

void Bank::setAmplitudeModulation(bool enable)
{
	disable_amplitude = !enable;
}


Oscill *Bank::oscillatorAt(int index) {
	return osc_ary+index;
}

