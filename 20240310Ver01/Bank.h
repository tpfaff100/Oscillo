#ifndef BANK_H
#define BANK_H

#include "Oscill.h"
#include "TextBitmap.h"

class Bank
{
private:
	Oscill *osc_ary;
	int osc_count;
	TextBitmap *surface;

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

	/** set drawing color for waveform on screen */
	virtual void setColor(int color);

	virtual Oscill *oscillatorAt(int index); 
};

#endif
