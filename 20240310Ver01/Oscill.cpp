#include <iostream>
#include <vector>
#include <cmath>
#include "Oscill.h"

using namespace std;


/** Initialize oscillator.  Each oscillator is a quadrature oscillator it (may have) a sin wave and a cosine wave.
 ** Other oscillators may be added as necessary **/

Oscill::Oscill() {
	/** ok typically this is a quadrature oscillator for now we support only sin+cos but we could in the
         ** future do something like support a triangle waveform with compatible phase values or we could
         ** add an oscillator or the Z axis.  Something like that.  This depends on your usecase. */
	
	o = new _osc_unit();
	o->sin = new Sin();
	o->cos = new Cos();

	o->scale = SCALE;

	o->range.low = 0.0;
	o->range.high = PI*2;		/* should let us draw one circle */

	axis_swap = false;		/* do not swap sin/cos across x/y axis by default */
	continuous = CONTINUOUS;	/* prep for CONTINUOUS waveform generation, not a ONESHOT cycle */

	chan1 = 0.0f;		/* these work out to integers and could be reconfigured as INT - optional compile time option maybe? */
	chan2 = 0.0f;
}

Oscill::Oscill(float rate) {
        o = new _osc_unit();
        o->sin = new Sin();
        o->cos = new Cos();

        o->sin->setIncRate(rate);
	o->cos->setIncRate(rate);

	o->scale = SCALE;

        o->range.low = 0.0;
        o->range.high = PI*2;           /* should let us draw one circle */

	axis_swap = false;
	continuous = CONTINUOUS;
	chan1 = 0.0f;
	chan2 = 0.0f;
}

Oscill::~Oscill() {
	if (o->sin != NULL)
		delete o->sin;
	if (o->cos != NULL)
		delete o->cos;

	if (o != NULL)
		delete o;
}

void Oscill::reset() {
	o->sin->reset();
	o->cos->reset();
}


bool Oscill::range(void) {
	next();
//printf ("%f %f\n", o->sin->current, o->range.high);
	if (o->sin->current > o->range.high) 
		return false;
	return true;
}



void Oscill::setRate(float rate) {
	o->sin->setIncRate(rate);
	o->cos->setIncRate(rate);
}


void Oscill::setPhaseO1(float phase) {
	o->sin->setPhase(phase);
}

void Oscill::setPhaseO2(float phase) {
	o->cos->setPhase(phase);
}


void Oscill::setRange(float low, float high) {
	o->range.low = low;
	o->range.high = high;
}

void Oscill::setContinous(OSCILL_PERSIST persist) {
	continuous = persist; 
}

void Oscill::setScale(int scale) {
	o->scale = scale;
}

bool Oscill::swap() {
	if (axis_swap == false)
		axis_swap = true;
	else 
		axis_swap = false;
	return axis_swap;
}

void Oscill::next(void) {
	if (axis_swap == false) {
		chan1 = o->sin->next() * float(o->scale);
		chan2 = o->cos->next() * float(o->scale);
	}
	else {
		chan1 = o->cos->next() * float(o->scale);
		chan2 = o->sin->next() * float(o->scale);
	}
	
	chan1 = SCALE/2 + chan1 / 2;
	chan2 = SCALE/2 + chan2 / 2;
}

