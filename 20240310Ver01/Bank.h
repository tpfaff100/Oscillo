#ifndef BANK_H
#define BANK_H

#include "Oscill.h"
#include "TextBitmap.h"
#include "Triangle.h"
#include "Sprite.h"

class Bank
{
private:
	Oscill *osc_ary;
	Triangle *color_mod_waveform; 	/* waveform that generates color variance as the bank draws itself */
	Triangle *amplitude_waveform;	/* modulate the output of the bank with an amplitude based oscillator */
	int osc_count;
	Sprite *sprite;
	TextBitmap *surface;

	bool disable_color_mod;
	bool disable_amplitude;

public:
	Bank();
	~Bank();
	Bank(Oscill *ary, int count);

	/** clear the bitmap */
	virtual void clear(void);

	/** draw the bitmap */
	virtual void dump(void);

	/** range() returns true until trigonometry range cycle is completed then returns false */
        virtual bool range(void);
	virtual void renderSpriteOffscreen(Sprite *sprite);
	virtual void setAmplitudeModulation(bool enable);
	virtual void setColorModulation(bool enable, Color color1, Color color2, float incrementRate); 
	virtual void setSprite(Sprite *sprite); 


	virtual Oscill *oscillatorAt(int index); 
};

#endif
