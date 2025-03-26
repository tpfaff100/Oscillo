#include <iostream>
#include "Trig.h"

using namespace std;


/** Trig and subclasses (Sin, Cos, Square, etc) are dumb waveform generators.
 **
 ** They do not check bounds or do anything smart.  They just pump out 
 ** values.  This is by design so that these classes can be easily replaced
 ** by lookup table classes someday or assembler language or whatever 
 **
 ** Ranges and value checking can be done manually or you can use the Oscill
 ** class to perform waveform changes when a value is exceeded.  Go there. 
 **
 ** I tend to make objects more complex than they should be.  By keeping
 ** the oscillator classes simple, I hope to keep some level of abstraction
 ** at this level that is SIMPLE and doesn't evolve into a complex mess.
 **
 ** So, try and keep this class and inherited classes as simple as possible.
 **
 ** Again, for any complex behavior, try to use these in an instance of Oscill.cpp.
 **
 ** 
 ** Expansion / performance option:
 **
 ** If you want to make waveform gen faster, you can create a subclass of say, Sin.cpp
 ** for a common set of increment values.  If the value is known, reference a set of
 ** table values for the sin values related to that increment.  
 ** .1, 01, .001 increment rates for instance.
 **
 ** If you're using many complex waveforms in concert
 ** together this would speed things up.  
 ** Especially on vintage computers w/out math coprocessors!
 **
 ** Even further, you could "integerize" the tables by creating a special subclass of
 ** Oscill.cpp that uses only integer lookup tables.  That could really speed things up!
 ** 
 ** OK you can see I have tried to leave all avenues open w/out adding much performance
 ** drag, other than the C++ polymorphism-based lookup/name-mangling costs, 
 ** which are hopefully small on your favorite modern/vintage platform.
 **
 ** If that sounds confusing forget about it and just use 
 ** Sin.cpp and Cos.cpp w/ no special cases and have fun.
*/



Trig::Trig() {
	incrate = DEFAULT_INCRATE;
	kInitial = 0.0f;
	current = kInitial;
	radians = 0.0f;
	phase = 0.0f;
}

Trig::Trig(float initial, float r, float p) {
        incrate = DEFAULT_INCRATE;
	kInitial = initial;
	current = initial;
	radians = r;
	phase = p;
}

void Trig::reset() {
	current = kInitial;
}

void Trig::setIncRate(float rate) {
	incrate = rate;
}

void Trig::setInitial(float val) {
        current = val;
}

void Trig::setRadians(float r) {
        radians = r;
}

void Trig::setPhase(float phase) {
        this->phase = phase;
}


