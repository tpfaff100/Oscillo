#ifndef PRESET_H
#define PRESET_H

#include <map>
#include <string>
#include <vector>

#include "Bank.h"

class Preset
{
	std::map<std::string, std::string> appsets;

	OscillVector osc_vec;	// own the oscillators for the lifetime of the preset
	Bank *bank = nullptr;	// collection of oscillators filled out and controlled by Preset.

	bool  getSwapStatus(std::string tagStr); 
	float getIncrementRate(std::string);
	int   getScaleConst(std::string); 

	int unitsToms(std::string data, std::string tag);

	float osc1_inc_rate = -1.0f, osc2_inc_rate = -1.0f, osc3_inc_rate = -1.0f,
	      osc4_inc_rate = -1.0f, osc5_inc_rate = -1.0f, osc6_inc_rate = -1.0f;
	int osc_count = 0;

	int osc1_scale, osc2_scale, osc3_scale, osc4_scale, osc5_scale, osc6_scale;
	int osc1_swap_axes, osc2_swap_axes, osc3_swap_axes, osc4_swap_axes, osc5_swap_axes, osc6_swap_axes;
	uint64_t duration = 0;
	uint64_t presetLoopYield = 0;

public:
	Preset(const std::vector<std::string>& filenames); 
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
