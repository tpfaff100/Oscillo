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

	// generic functiosn to convert JSON string from file to C datatype.  
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

	// enable amplitude modulation on the oscillator bank. 
	bool bAmpMod;	
	float fAmpModIncRate;

	// color modulation information- this lets colors animate sync'd to the trig waveform while shape is animating. 
        int bColorEnable;
	float fColorModIncRate;

        Color colorMod1;
        Color colorMod2;

	// each Bank has 6 'x axis oscillators' and 6 'y axis oscillators.  we can control starting/relative phase shift here.
	float fOsc1PhaseX = 0.0f, fOsc2PhaseX = 0.0f, fOsc3PhaseX = 0.0f, fOsc4PhaseX = 0.0f, fOsc5PhaseX = 0.0f, fOsc6PhaseX = 0.0f;
	float fOsc1PhaseY = 0.0f, fOsc2PhaseY = 0.0f, fOsc3PhaseY = 0.0f, fOsc4PhaseY = 0.0f, fOsc5PhaseY = 0.0f, fOsc6PhaseY = 0.0f;

	// general class vars for Preset object 

	// we need the start time and a duration to calculate how long to keep plotting the graph for.
//	long long llStartTime = 0.0;
	long long llExpiryTime = 0.0;
	uint64_t duration = 10000;

	uint64_t presetLoopYield = 0;

public:
	Preset(const std::vector<std::string>& filenames); 
	Preset(std::string file);
	~Preset();

	// perform one waveform iteration only 
	void clear();

	// we have the option of merging presets and bitmaps to draw one single bitmap.  Normally sends nullptr. 
	bool iterate(Preset *p2);	
	void sleep();

	// perform an entire cycle through the waveform per loaded preset file 
	int run(void);
};

#endif
