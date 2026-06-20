#ifndef PRESET_H
#define PRESET_H

#include <map>
#include <string>
#include "Bank.h"

class Preset
{
	std::map<std::string, std::string> appsets;

	OscillVector osc_vec;	// own the oscillators for the lifetime of the preset
	Bank *bank;	// collection of oscillators filled out and controlled by Preset.

	float getIncrementRate(std::string);
	int unitsToms(std::string data, std::string tag);

	float osc1_inc_rate, osc2_inc_rate, osc3_inc_rate, osc4_inc_rate, osc5_inc_rate, osc6_inc_rate;
	int osc_count;
	uint64_t duration;
	uint64_t presetLoopYield;

public:
	Preset(std::string file);
	~Preset();

	/** perform one waveform iteration only */
	void clear();

	/** we have the option of merging presets and bitmaps to draw one single bitmap.  Normally sends nullptr. */
	bool iterate(Preset *p2);	
	void sleep();

	/** perform an entire cycle through the waveform per loaded preset file */
	int run(void);
};

#endif
