#ifndef PRESET_H
#define PRESET_H

#include <map>
#include <string>
#include <vector>

#include "Bank.h"
#include "TextBitmap.h"		// colors


class Preset
{
	std::map<std::string, std::string> appsets;

	OscillVector osc_vec;	// own the oscillators for the lifetime of the preset
	Bank *bank = nullptr;	// collection of oscillators filled out and controlled by Preset.

	float getAmplitudeMod(std::string);

	Color getColorMod(std::string);
	bool  jsonStrToBool(std::string); 
	float jsonStrToFloat(std::string);
	int   jsonStrToInt(std::string); 

	int unitsToms(std::string data, std::string tag);

	float fOsc1IncRate = -1.0f, fOsc2IncRate = -1.0f, fOsc3IncRate = -1.0f,
	      fOsc4IncRate = -1.0f, fOsc5IncRate = -1.0f, fOsc6IncRate = -1.0f;
	int osc_count = 0;

	int osc1Scale, osc2Scale, osc3Scale, osc4Scale, osc5Scale, osc6Scale;
	bool bOsc1SwapAxes, bOsc2SwapAxes, bOsc3SwapAxes, bOsc4SwapAxes, bOsc5SwapAxes, bOsc6SwapAxes;

	bool bAmpMod;	// enable amplitude modulation on the oscillator bank.

	/* color modulation information- this lets colors animate sync'd to the trig waveform while shape is animating. */
        int bColorEnable;
	float fColorModIncRate;

        Color colorMod1;
        Color colorMod2;

	/* general class vars for Preset object */
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
