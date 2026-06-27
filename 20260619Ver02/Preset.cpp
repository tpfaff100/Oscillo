/** Preset.cpp - 2026.0619 - TCP
 **
 ** Loads a preset from one file and creates a bank of oscillators on the x+y access for ONE PLOT only
 **
 ** If you want multiple waveforms on the screen at a time you must create multiple
 **  Prests/Banks of oscillators.  Do not expect a Preset to hold more than one set of oscillators
 **  By design it will only draw one x/y plot from a collection of oscillators.
 **
 ** However, note you can have six x/y oscillators encapsulated in a Preset.
 ** These oscillators will cycle and have their results added to final input 
 ** per the PRESET instructions from any preset file.
 **
 ** Remember - ONE SET OF WAVEFORMS PER PRESET!  (think of it like an old car radio station button)
 **
 ** Create multiple presets and ->run() them at the same time if you like.
 **
 **/

#include <chrono>	// time functions
#include <fstream>
#include <iostream>     // std::cout
#include <map>
#include <sstream>      // std::istringstream
#include <string>       // std::string
#include <vector>
#include <unistd.h>	// std::usleep

#include "Preset.h"
#include "Bank.h"
#include "Oscill.h"

#define TAG_DELAY		"initial_delay"
#define TAG_DURATION		"duration"
#define TAG_FILE		"file"
#define TAG_LOOP_YIELD_DELAY	"loop_yield_time"

#define TAG_OSC1_PHASEX		"osc1_phase_x"
#define TAG_OSC2_PHASEX		"osc2_phase_x"
#define TAG_OSC3_PHASEX		"osc3_phase_x"
#define TAG_OSC4_PHASEX		"osc4_phase_x"
#define TAG_OSC5_PHASEX		"osc5_phase_x"
#define TAG_OSC6_PHASEX		"osc6_phase_x"

#define TAG_OSC1_PHASEY         "osc1_phase_y"
#define TAG_OSC2_PHASEY         "osc2_phase_y"
#define TAG_OSC3_PHASEY         "osc3_phase_y"
#define TAG_OSC4_PHASEY         "osc4_phase_y"
#define TAG_OSC5_PHASEY         "osc5_phase_y"
#define TAG_OSC6_PHASEY         "osc6_phase_y"

#define TAG_OSC1_INC_RATE	"osc1_inc_rate"
#define TAG_OSC2_INC_RATE	"osc2_inc_rate"
#define TAG_OSC3_INC_RATE	"osc3_inc_rate"
#define TAG_OSC4_INC_RATE	"osc4_inc_rate"
#define TAG_OSC5_INC_RATE	"osc5_inc_rate"
#define TAG_OSC6_INC_RATE	"osc6_inc_rate"

#define TAG_OSC1_SETSCALE	"osc1_set_scale"
#define TAG_OSC2_SETSCALE	"osc2_set_scale"
#define TAG_OSC3_SETSCALE	"osc3_set_scale"
#define TAG_OSC4_SETSCALE	"osc4_set_scale"
#define TAG_OSC5_SETSCALE	"osc5_set_scale"
#define TAG_OSC6_SETSCALE	"osc6_set_scale"

#define TAG_OSC1_SWAP_AXES	"osc1_swap_axes"
#define TAG_OSC2_SWAP_AXES	"osc2_swap_axes"
#define TAG_OSC3_SWAP_AXES	"osc3_swap_axes"
#define TAG_OSC4_SWAP_AXES	"osc4_swap_axes"
#define TAG_OSC5_SWAP_AXES	"osc5_swap_axes"
#define TAG_OSC6_SWAP_AXES	"osc6_swap_axes"

#define TAG_AMPLITUDE_MOD	"amplitude_modulation"

#define TAG_COLOR_MOD_ENABLE	"color_mod_enable"
#define TAG_COLOR_1		"color_mod1"
#define TAG_COLOR_2		"color_mod2"
#define TAG_COLOR_MOD_INC_RATE	"color_mod_inc_rate"


using namespace std;
using namespace std::chrono;



uint64_t timeSinceEpochMillisec() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}


std::string trim(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isspace(*it))
        it++;

    std::string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && isspace(*rit))
        rit++;

    return std::string(it, rit.base());
}


std::string first_number_in_str(std::string const & str)
{
      char const* digits = "0123456789";
      std::size_t const n = str.find_first_of(digits);
      if (n != std::string::npos)
      {
        std::size_t const m = str.find_first_not_of(digits, n);
        return str.substr(n, m != std::string::npos ? m-n : m);
      }
      return std::string();
}


std::string first_units_in_str(std::string const & str)
{
      char const* digits = "ms";
      std::size_t const n = str.find_first_of(digits);
      if (n != std::string::npos)
      {
        std::size_t const m = str.find_first_not_of(digits, n);
        return str.substr(n, m != std::string::npos ? m-n : m);
      }
      return std::string();
}


// NOTE:  RENDERS ONE OR MORE PRESET FILES AT A TIME from a list/vector of presetfiles.
// Render one or more prs/PRESET files and produce waveform output inr eal time based on instructions contained within 
Preset::Preset(const std::vector<std::string>& filenames) {
	std::cout << "Processing " << filenames.size() << " files:\n";

	std::vector<Preset> vPresets;
	vPresets.reserve(filenames.size());

	for (const std::string& file : filenames) {
		std::cout << " - " << file << "\n";
		vPresets.emplace_back(file);
	}

	if (vPresets.empty()) {
		cout << "Error:  No preset files were specified.\n";
		return;
	}

	bool isComplete = false;
	do
	{
		int preset_count = 0;	
		for (Preset& preset : vPresets) {
			if (preset_count++ == 0) {
				isComplete = preset.iterate(NULL);
				preset.iterate(NULL);
				preset.clear();
				preset.sleep();
				std::system("clear");

				if (isComplete == true)
					return;
			}
			else {
				preset.iterate(&vPresets[0]);
				preset.sleep();
			}
		}
	}
	while(isComplete==false); 	

}


// NOTE:  RENDERS ONLY ONE PRESET FILE AT A TIME at the file/pathname given.
// load one prs/PRESET file and produce waveform output in real time based on the instructions contained within
Preset::Preset(std::string filename) {

	std::string line;
	std::ifstream rfile;

	rfile.open(filename);

	// load 'prs' (preset) file ==> produce waveforms as per instructions in the preset file.
	if (rfile.is_open()) {
		while (std::getline(rfile, line)) {
			if (line.front() != '#') {	// a '#' at position 0 in presets file indicates line should be ignored
				int pos = line.find("=");
				if (pos > -1) {
					line = trim(line);
					unsigned first = line.find("\"");
					unsigned last = line.find_last_of("\"");

					if (last > first) {
						string key = line.substr( 0, first-1);
						string attr = line.substr (first+1,last-first-1);
						appsets[key] = attr;
					}
				}
			}
		}
	}
	rfile.close();

        // Load whatever is spec'd in the presets file.
        // (no one will ever need more than six quadrature oscillators, right?  )
        fOsc1IncRate = jsonStrToFloat( TAG_OSC1_INC_RATE);
        fOsc2IncRate = jsonStrToFloat( TAG_OSC2_INC_RATE);
        fOsc3IncRate = jsonStrToFloat( TAG_OSC3_INC_RATE);
        fOsc4IncRate = jsonStrToFloat( TAG_OSC4_INC_RATE);
        fOsc5IncRate = jsonStrToFloat( TAG_OSC5_INC_RATE);
        fOsc6IncRate = jsonStrToFloat( TAG_OSC6_INC_RATE);
        osc_count = (fOsc1IncRate > 0) + (fOsc2IncRate > 0) + (fOsc3IncRate > 0) +
                        (fOsc4IncRate > 0) + (fOsc5IncRate > 0) + (fOsc6IncRate > 0);

//	if (osc_count == 0 && appsets[TAG_FILE].length() == 0 ) {
	if (osc_count == 0) {
                cout << "At least one oscillator or animation must be defined in the preset file\nExiting...\n";
                exit(1);
        }

	fOsc1PhaseX = jsonStrToFloat( TAG_OSC1_PHASEX);
	fOsc2PhaseX = jsonStrToFloat( TAG_OSC2_PHASEX);
	fOsc3PhaseX = jsonStrToFloat( TAG_OSC3_PHASEX);
	fOsc4PhaseX = jsonStrToFloat( TAG_OSC4_PHASEX);
	fOsc5PhaseX = jsonStrToFloat( TAG_OSC5_PHASEX);
	fOsc6PhaseX = jsonStrToFloat( TAG_OSC6_PHASEX);

	fOsc1PhaseY = jsonStrToFloat( TAG_OSC1_PHASEY);
	fOsc2PhaseY = jsonStrToFloat( TAG_OSC2_PHASEY);
	fOsc3PhaseY = jsonStrToFloat( TAG_OSC3_PHASEY);
	fOsc4PhaseY = jsonStrToFloat( TAG_OSC4_PHASEY);
	fOsc5PhaseY = jsonStrToFloat( TAG_OSC5_PHASEY);
	fOsc6PhaseY = jsonStrToFloat( TAG_OSC6_PHASEY);

	osc1Scale = jsonStrToInt( TAG_OSC1_SETSCALE );
	osc2Scale = jsonStrToInt( TAG_OSC2_SETSCALE );
	osc3Scale = jsonStrToInt( TAG_OSC3_SETSCALE );
	osc4Scale = jsonStrToInt( TAG_OSC4_SETSCALE );
	osc5Scale = jsonStrToInt( TAG_OSC5_SETSCALE );
	osc6Scale = jsonStrToInt( TAG_OSC6_SETSCALE );

	bOsc1SwapAxes = jsonStrToBool( TAG_OSC1_SWAP_AXES );
	bOsc2SwapAxes = jsonStrToBool( TAG_OSC2_SWAP_AXES );
	bOsc3SwapAxes = jsonStrToBool( TAG_OSC3_SWAP_AXES );
	bOsc4SwapAxes = jsonStrToBool( TAG_OSC4_SWAP_AXES );
	bOsc5SwapAxes = jsonStrToBool( TAG_OSC5_SWAP_AXES );
	bOsc6SwapAxes = jsonStrToBool( TAG_OSC6_SWAP_AXES );

	bAmpMod = jsonStrToBool( TAG_AMPLITUDE_MOD );

	fColorModIncRate = jsonStrToFloat( TAG_COLOR_MOD_INC_RATE );
	colorMod1 = getColorMod( TAG_COLOR_1);
	colorMod2 = getColorMod( TAG_COLOR_2);
	bColorEnable = jsonStrToBool ( TAG_COLOR_MOD_ENABLE );

        Oscill a(fOsc1IncRate);
        Oscill b(fOsc2IncRate);
        Oscill c(fOsc3IncRate);
        Oscill d(fOsc4IncRate);
        Oscill e(fOsc5IncRate);
        Oscill f(fOsc6IncRate);


	//if the oscillator was configured, save it for later / add it to the collection class.
        if (fOsc1IncRate > 0) {
		a.setPhaseO1(fOsc1PhaseX);
		a.setPhaseO2(fOsc1PhaseY);
		a.setScale(osc1Scale);
		if (bOsc1SwapAxes) a.swap();
                osc_vec.push_back(a);
        }
	if (fOsc2IncRate > 0) {
		b.setPhaseO1(fOsc2PhaseX);
		b.setPhaseO2(fOsc2PhaseY);
		b.setScale(osc2Scale);
		if (bOsc2SwapAxes) b.swap();
                osc_vec.push_back(b);
        }
	if (fOsc3IncRate > 0) {
		c.setPhaseO1(fOsc3PhaseX);
		c.setPhaseO2(fOsc3PhaseY);
		c.setScale(osc3Scale);
		if (bOsc3SwapAxes) c.swap();
                osc_vec.push_back(c);
        }
	if (fOsc4IncRate > 0) {
		d.setPhaseO1(fOsc4PhaseX);
		d.setPhaseO2(fOsc4PhaseY);
		d.setScale(osc4Scale);
		if (bOsc4SwapAxes) d.swap();
                osc_vec.push_back(d);
        }
	if (fOsc5IncRate > 0) {
		e.setPhaseO1(fOsc5PhaseX);
		e.setPhaseO2(fOsc5PhaseY);
		e.setScale(osc5Scale);
		if (bOsc5SwapAxes) e.swap();
                osc_vec.push_back(e);
        }
	if (fOsc6IncRate > 0) {
		f.setPhaseO1(fOsc6PhaseX);
		f.setPhaseO2(fOsc6PhaseY);
		f.setScale(osc6Scale);
		if (bOsc6SwapAxes) f.swap();
                osc_vec.push_back(f);
	}

        bank = new Bank(osc_vec);
	bank->setAmplitudeModulation(bAmpMod);

	if (bColorEnable == true)
		bank->setColorModulation(bColorEnable, colorMod1, colorMod2, fColorModIncRate);      /* optional, color modulation is off by default */

#ifndef NDEBUG
        std::cerr << "Preset debug: rates="
                  << fOsc1IncRate << ","
                  << fOsc2IncRate << ","
                  << fOsc3IncRate << ","
                  << fOsc4IncRate << ","
                  << fOsc5IncRate << ","
                  << fOsc6IncRate 
                  << " osc_count=" << osc_count
                  << " vector_size=" << osc_vec.size()
                  << std::endl;
#endif

        uint64_t delay =       unitsToms( appsets[TAG_DELAY], TAG_DELAY );
        usleep(delay*1000);	// convert millseconds to microseconds for usleep()

        duration =             unitsToms( appsets[TAG_DURATION], TAG_DURATION );
        presetLoopYield =      unitsToms( appsets[TAG_LOOP_YIELD_DELAY], TAG_LOOP_YIELD_DELAY );
//cout << "\n" << presetLoopYield << endl;
//exit(0);

        Sprite *sprite = new Sprite(appsets[TAG_FILE], 23);     // optionally load a sprite.
        bank->setSprite(sprite);       // attach the animation to the oscillator bank.

        llExpiryTime = timeSinceEpochMillisec() + duration;
	std::cout << "\n\n" << delay << std::endl;
	std::cout << duration << std::endl;
	std::cout << llExpiryTime << std::endl;
	std::cout << timeSinceEpochMillisec() << std::endl;
}


Preset::~Preset() {
//check - remember to come back and deallocate 'sprite' from the bank
	if (bank != nullptr) {
		delete bank;
		bank = nullptr;
	}
}





Color Preset::getColorMod(std::string tagStr) {
        string str = appsets[tagStr];

	if (str == "red")
		return red;
	if (str == "green")
		return green;
	if (str == "yellow")
		return yellow;
	if (str == "purple")
		return purple;
	if (str == "cyan")
		return cyan;
	if (str == "white")
		return white;
	if (str == "black")
		return black; 
	return green;
}


bool Preset::jsonStrToBool(std::string tagStr) {
	string str = appsets[tagStr];

	if (str.length() > 0) {				// if the tag exists.
		if (str == "true") {
			return true;
		}
	}
	return false;
}


// check the incoming string
float Preset::jsonStrToFloat(std::string tagStr) {
	string str = appsets[tagStr];
	float incRate = -1.0f;				// -1 ==> no such tag or element

	if (str.length() > 0) {				// if the tag exists.
		incRate = std::stof(appsets[tagStr]);	// get the attribute/element.
	}
	return incRate;
}


int Preset::jsonStrToInt(std::string tagStr) {
	string str = appsets[tagStr];
	int scale=SCALE;				// default set in Oscill.h

	if (str.length() > 0) {				// if the tag exists.
		scale = std::stof(appsets[tagStr]);	// get the attribute/element.
	}
	return scale;
}



// we get a tag/string with units in it.  We look at the units
// and convert to microseconds because that is what usleep() takes.
// supported units:  (s)econds and (ms) milleseconds
int Preset::unitsToms(string data, string tag) {
        string num = first_number_in_str(appsets[tag]);
        string units = first_units_in_str(appsets[tag]);
//cout << num + " " + units;
        int time_in_ms = std::stoi(num);	// currently time in whatever units specified.

	if (units == "s" || units == "sec" || units == "seconds")
		time_in_ms *= 1000; 		// convert seconds to milleseconds and keep value.
	if (units == "m" || units == "min" || units == "minutes")
		time_in_ms *= 60000;		// convert minutes to milleseconds and keep value.
	if (units == "h" || units == "hour" || units == "hours")
		time_in_ms *= 3600000;
	return time_in_ms;
}


void Preset::clear() {
	if (bank != nullptr)
		bank->clear();
}

void Preset::sleep() {
	usleep(presetLoopYield*1000);	// sleep for n000 us aka  n ms)
}	


/* async callback - this runs the preset through one interation and then returns.
 * returns false if our time is up
 */
bool Preset::iterate(Preset *p2) {
	Bank *b2 = NULL;	// by default, B2 is null, which means we use our own framebuffer!
	long long cur_time = timeSinceEpochMillisec();

	if (p2 != NULL)
		b2 = p2->bank;
	while(bank->range(b2))   // compute all values for one cycle, whatever that was predetermined to be.
		;               // yes the semicolon is necessary.  Do not delete it!

	bank->dump();          // draw the cycle of waveforms and animation frame, where appropriate.
#if NDEBUG
printf("cur_time:%ld  time left:%ld\n",  cur_time, llExpiryTime-cur_time);
#endif
	if (llExpiryTime-cur_time < 0)
		return true;
	return false;
}


// this synchronous method runs the preset as quickly as possible in a loop; does not exit until done.
int Preset::run() {
	long long llExpiryTime = timeSinceEpochMillisec() + duration/1000, cur_time = 0;

	// A N I M A T E   O U R   T R I G   F U N C T I O N S
	////////////////////////////////////////////////////////////
	// run a trigonometric animation cycle for awhile.
	do {
		cur_time = timeSinceEpochMillisec();

		// this loop executes quickly in some sort of fraction of a second, depending on predetermined cycle+resolution
		while(bank->range(NULL)) 	// compute all values for one cycle, whatever that was predetermined to be.
			;		// yes the semicolon is necessary.  Do not delete it!


		bank->dump();          // draw the cycle of waveforms and animation frame, where appropriate.
		usleep(presetLoopYield);// wait awhile.
		bank->clear();		// clear the bitmap.
		std::system("clear");	// clear the screen.

	}
	while(llExpiryTime - cur_time > 0);
	return 0;
}
