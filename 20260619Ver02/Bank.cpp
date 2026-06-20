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

Bank::Bank(OscillVector& oscs) : osc_vec(oscs) {
	surface = new TextBitmap();
	sprite = NULL;

	color_mod_waveform = new Triangle();	// oscillator used to implement color cycling.
	color_mod_waveform->setIncRate(.02);
	disable_color_mod = true;
	disable_amplitude = true;
	
	amplitude_waveform.setIncRate(.01);
}


Bank::~Bank() {
	if (surface != NULL)
		delete surface;
	if (color_mod_waveform != NULL)
		delete color_mod_waveform;
}


// draw a 1980s vt100 animation sprite frame into the text framebuffer.
void Bank::renderSpriteOffscreen(Sprite *sprite) {
        if (sprite != NULL) {
		string framestr = sprite->next();
                int height = sprite->frame_height;
                int bx = SCALE/2 - sprite->frame_width/2, by = SCALE/2 - sprite->frame_height/2;
		int resetx = bx;
                char pixel = ' ';

		int count = 0;
                // xfer the antiquated vt100 frame to our super high-tech text framebuffer!
                for (int row = 0; row < height; row++) {
                        do {
				if (by < SCALE && by > 0) {
					pixel = framestr[count++];
					surface->bmap[bx++][by] = pixel;
				}
                        } while( pixel != '\n');

			surface->bmap[bx-1][by] = ' ';	// remove the CR from the end of the line.
                        bx = resetx;
                        by++;
                }
        }
}


/** call this until receiving a FALSE condition.  FALSE indicates the end of a cycle
 ** based on the 0th oscillator's state only.  
 **
 ** @Bbank2 - if present, we write into Bank's framebuffer.  This lets us have one drawing surface for two separate Presets
 **                   kinda not the neatest code but it keeps things fairly fast
 */
bool Bank::range(Bank *b2) {
	bool inrange = false;
	int x = 0, y = 0;
	int osc_count = osc_vec.size();
	TextBitmap *tbm = NULL;

	if (b2 != NULL)
		tbm = b2->surface;

	if (sprite != NULL) 
		renderSpriteOffscreen(this->sprite);

	for (int count = osc_count-1; count >= 0; count--) {
		Oscill& o = osc_vec.at(count);
		inrange = o.range();

		// if an oscillator is in "one-shot" mode it stops oscillating after it completes its cycle/range.
		if (o.continuous == CONTINUOUS)
		{
			if (inrange == false) {		// this should only happen once an animation frame ==> not wasting a lot of cycles here.
				if (!disable_amplitude) { 	// tickle the amplitude waveform oscillator once every animation frame.
					o.setScale(SCALE*amplitude_waveform.next());	
				}
//check
//printf("%f\n", SCALE*amplitude_waveform.next());
				o.reset();
			}
		}
		x += int(o.chan1);
		y += int(o.chan2);

//printf("%d) %d %d\n", count,x,y);
	}
	x = x / osc_count;
	y = y / osc_count;

	TextBitmap *tsurface = surface;		// store this class's surface away
	if (tbm != NULL)				// allow another surface to pose as ours for combined blits.
		surface = tbm;

	if (disable_color_mod == false) {
		if (color_mod_waveform->next() > 0.0)
			surface->bmap[x][y] = '.';    // write a 'pixel' to the offscreen bitmap.
		else
			surface->bmap[x][y] = '*';    // write a 'pixel' to the offscreen bitmap.

	} else {				// no color modulation so let's keep it simple!
		surface->bmap[x][y] = '*';	// colorless. Runs faster/cleaner w/ complex shapes.
	}

	surface = tsurface;	// restore this class's surface instance.


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

