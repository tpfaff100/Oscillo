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

	virtual void clear(void);
	virtual void dump(void);
        virtual bool range(void);

	virtual Oscill *oscillatorAt(int index); 
};

#endif
