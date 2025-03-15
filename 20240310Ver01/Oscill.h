#ifndef OSCILL_H
#define OSCILL_H

#define SCALE           60 

#include "Sin.h"
#include "Cos.h"

enum OSCILL_PERSIST { ONESHOT, CONTINUOUS };	// basically oscillator persistance is either 0=false or 1=true!

// range over which an oscillator operates when iterated
class Range
{
public:
	float low;
	float high;
};

/** Quadrature oscillator data and our total range for which to exercise the waveform(s).
  * The "Oscill" object contains two waveforms that are typically used to build a 
  * quadatrue oscillator, encapsulating sin and cos waves.  The intent is to project
  * sin wave OR cos wave on either axis */
class _osc_unit
{
public:
	Sin *sin;
	Cos *cos;
	int scale;
	Range range;
};


class Oscill 
{
private:
	_osc_unit *o;
	bool axis_swap;		// normally, sin is plotted on the x axis w/ cos on the y axis.  if true, the axes are inverted.
public:
	float chan1, chan2;
	OSCILL_PERSIST continuous;	/** signify whether this is a one-shot oscillator of if it runs continuously */

	Oscill();
	Oscill(float rate);
	~Oscill();

	/** use preset increment to calculate next oscillation value (e.g. sin or cos) */
	virtual void next(void);

	/** reset the range used to evaluate the oscillator */
	virtual void reset(void);
	
	/** swap sin/cos on the x,y axis, respectively */
	virtual bool swap();

	virtual bool range(void);

	/** oscillators either run oneshot (one cycle or range) or they run continuously */
	virtual void setContinous(OSCILL_PERSIST persist);

	/** set sin wave phase for only the first oscillator */
	virtual void setPhaseO1(float phase);

	/** set sin wave phase for only the second oscillator */
	virtual void setPhaseO2(float phase);

	virtual void setRange(float low, float high);
	virtual void setRate(float rate);
	virtual void setScale(int scale); 
};

#endif
