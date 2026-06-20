#ifndef TRIG_H
#define TRIG_H

#define PI			3.14159265358979
#define DEFAULT_INCRATE		0.1


class Trig
{
public:
	float current;
        float phase;

protected:	
        float radians;
        float incrate;

	float kInitial;

public:
	Trig();
	Trig(float initial, float radians, float phase); 

	virtual float eval(float) = 0;
	virtual float next(void) = 0;

	virtual void reset(void);
	virtual void setInitial(float val);
	virtual void setRadians(float r); 
	virtual void setIncRate(float r);
	virtual void setPhase(float phase); 
};

#endif
