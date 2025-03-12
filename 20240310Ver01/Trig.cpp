#include <iostream>
#include "Trig.h"

using namespace std;

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


