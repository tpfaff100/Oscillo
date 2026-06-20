#ifndef BANK_H
#define BANK_H

#include <vector>
#include <list>
#include "Oscill.h"
#include "OscillVector.h"
#include "TextBitmap.h"
#include "Triangle.h"
#include "Sprite.h"
#include "TextBitmap.h"

class Bank
{
private:
	OscillVector& osc_vec;

	Triangle *color_mod_waveform; 	/* waveform that generates color variance as the bank draws itself */
	Triangle amplitude_waveform;	/* modulate the output of the bank with an amplitude based oscillator */
	Sprite *sprite;

	bool disable_color_mod;
	bool disable_amplitude;

public:
	TextBitmap *surface;

	Bank(OscillVector& oscs);
	~Bank();


	/** clear the bitmap */
	virtual void clear(void);

	/** draw the bitmap */
	virtual void dump(void);

	/** range() returns true until trigonometry range cycle is completed then returns false */
        virtual bool range(Bank *bank2);
	virtual void renderSpriteOffscreen(Sprite *sprite);
	virtual void setAmplitudeModulation(bool enable);
	virtual void setColorModulation(bool enable, Color color1, Color color2, float incrementRate); 
	virtual void setSprite(Sprite *sprite); 
};

#endif
