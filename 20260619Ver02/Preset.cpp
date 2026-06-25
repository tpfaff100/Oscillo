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

#define TAG_DELAY		"initial_delay"
#define TAG_DURATION		"duration"
#define TAG_FILE		"file"
#define TAG_LOOP_YIELD_DELAY	"loop_yield_time"

#define TAG_OSC1_INC_RATE	"osc1_inc_rate"
#define TAG_OSC2_INC_RATE	"osc2_inc_rate"
#define TAG_OSC3_INC_RATE	"osc3_inc_rate"
#define TAG_OSC4_INC_RATE	"osc4_inc_rate"
#define TAG_OSC5_INC_RATE	"osc5_inc_rate"
#define TAG_OSC6_INC_RATE	"osc6_inc_rate"


#define TAG_OSC1_SETSCALE	"osc1_setscale"
#define TAG_OSC2_SETSCALE	"osc2_setscale"
#define TAG_OSC3_SETSCALE	"osc3_setscale"
#define TAG_OSC4_SETSCALE	"osc4_setscale"
#define TAG_OSC5_SETSCALE	"osc5_setscale"
#define TAG_OSC6_SETSCALE	"osc6_setscale"

#define TAG_OSC1_SWAP_AXES	"osc1_swap_axes"
#define TAG_OSC2_SWAP_AXES	"osc2_swap_axes"
#define TAG_OSC3_SWAP_AXES	"osc3_swap_axes"
#define TAG_OSC4_SWAP_AXES	"osc4_swap_axes"
#define TAG_OSC5_SWAP_AXES	"osc5_swap_axes"
#define TAG_OSC6_SWAP_AXES	"osc6_swap_axes"


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


Preset::Preset(const std::vector<std::string>& filenames) {
	std::cout << "Processing " << filenames.size() << " files:\n";

	std::vector<Preset> vPresets;
	vPresets.reserve(filenames.size());

	for (const std::string& file : filenames) {
		std::cout << " - " << file << "\n";
		vPresets.emplace_back(file);
	}

	if (vPresets.empty()) {
		return;
	}

	while( 1) {

		int preset_count = 0;	
		for (Preset& preset : vPresets) {
			if (preset_count++ == 0) {
				preset.iterate(NULL);
				preset.clear();
				preset.sleep();
				std::system("clear");
			}
			else
				preset.iterate(&vPresets[0]);
		}
	}

}

Preset::Preset(std::string filename) {

	std::string line;
	std::ifstream rfile;

	rfile.open(filename);


	if (rfile.is_open()) {
		while (std::getline(rfile, line)) {
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
	rfile.close();

        // Load whatever is spec'd in the presets file.
        // (no one will ever need more than six quadrature oscillators, right?  )
        osc1_inc_rate = getIncrementRate( TAG_OSC1_INC_RATE);
        osc2_inc_rate = getIncrementRate( TAG_OSC2_INC_RATE);
        osc3_inc_rate = getIncrementRate( TAG_OSC3_INC_RATE);
        osc4_inc_rate = getIncrementRate( TAG_OSC4_INC_RATE);
        osc5_inc_rate = getIncrementRate( TAG_OSC5_INC_RATE);
        osc6_inc_rate = getIncrementRate( TAG_OSC6_INC_RATE);
        osc_count = (osc1_inc_rate > 0) + (osc2_inc_rate > 0) + (osc3_inc_rate > 0) +
                        (osc4_inc_rate > 0) + (osc5_inc_rate > 0) + (osc6_inc_rate > 0);

        if (osc_count == 0) {
                cout << "At least one oscillator must be defined in the preset file\nExiting...\n";
                exit(1);
        }

	osc1_scale = getScaleConst( TAG_OSC1_SETSCALE );
	osc2_scale = getScaleConst( TAG_OSC2_SETSCALE );
	osc3_scale = getScaleConst( TAG_OSC3_SETSCALE );
	osc4_scale = getScaleConst( TAG_OSC4_SETSCALE );
	osc5_scale = getScaleConst( TAG_OSC5_SETSCALE );
	osc6_scale = getScaleConst( TAG_OSC6_SETSCALE );

	osc1_swap_axes = getSwapStatus( TAG_OSC1_SWAP_AXES );
	osc2_swap_axes = getSwapStatus( TAG_OSC2_SWAP_AXES );
	osc3_swap_axes = getSwapStatus( TAG_OSC3_SWAP_AXES );
	osc4_swap_axes = getSwapStatus( TAG_OSC4_SWAP_AXES );
	osc5_swap_axes = getSwapStatus( TAG_OSC5_SWAP_AXES );
	osc6_swap_axes = getSwapStatus( TAG_OSC6_SWAP_AXES );


        Oscill a(osc1_inc_rate);
        Oscill b(osc2_inc_rate);
        Oscill c(osc3_inc_rate);
        Oscill d(osc4_inc_rate);
        Oscill e(osc5_inc_rate);
        Oscill f(osc6_inc_rate);

	//if the oscillator was configured, save it for later / add it to the collection class.
        if (osc1_inc_rate > 0) {
		a.setScale(osc1_scale);
		if (osc1_swap_axes) a.swap();
                osc_vec.push_back(a);
        }
	if (osc2_inc_rate > 0) {
		b.setScale(osc2_scale);
		if (osc2_swap_axes) b.swap();
                osc_vec.push_back(b);
        }
	if (osc3_inc_rate > 0) {
		c.setScale(osc3_scale);
		if (osc3_swap_axes) c.swap();
                osc_vec.push_back(c);
        }
	if (osc4_inc_rate > 0) {
		d.setScale(osc4_scale);
		if (osc4_swap_axes) d.swap();
                osc_vec.push_back(d);
        }
	if (osc5_inc_rate > 0) {
		e.setScale(osc5_scale);
		if (osc5_swap_axes) e.swap();
                osc_vec.push_back(e);
        }
	if (osc6_inc_rate > 0) {
		f.setScale(osc6_scale);
		if (osc6_swap_axes) f.swap();
                osc_vec.push_back(f);
	}

        bank = new Bank(osc_vec);

#ifndef NDEBUG
        std::cerr << "Preset debug: rates="
                  << osc1_inc_rate << ","
                  << osc2_inc_rate << ","
                  << osc3_inc_rate << ","
                  << osc4_inc_rate << ","
                  << osc5_inc_rate << ","
                  << osc6_inc_rate
                  << " osc_count=" << osc_count
                  << " vector_size=" << osc_vec.size()
                  << std::endl;
#endif

        uint64_t delay =                unitsToms( appsets[TAG_DELAY], TAG_DELAY );
        usleep(delay);

        duration =             unitsToms( appsets[TAG_DURATION], TAG_DURATION );
        presetLoopYield =      unitsToms( appsets[TAG_LOOP_YIELD_DELAY], TAG_LOOP_YIELD_DELAY );

        Sprite *sprite = new Sprite(appsets[TAG_FILE], 23);     // optionally load a sprite.
        bank->setSprite(sprite);       // attach the animation to the oscillator bank.


//	std::cout << timeSinceEpochMillisec() << std::endl;
}


Preset::~Preset() {
//check - remember to come back and deallocate 'sprite' from the bank
	if (bank != nullptr) {
		delete bank;
		bank = nullptr;
	}
}


bool Preset::getSwapStatus(std::string tagStr) {
	string str = appsets[tagStr];

	if (str.length() > 0) {				// if the tag exists.
		if (str == "true") {
			return true;
		}
	}
	return false;
}


// check the incoming string
float Preset::getIncrementRate(std::string tagStr) {
	string str = appsets[tagStr];
	float incRate = -1.0f;				// -1 ==> no such tag or element

	if (str.length() > 0) {				// if the tag exists.
		incRate = std::stof(appsets[tagStr]);	// get the attribute/element.
	}
	return incRate;
}


int Preset::getScaleConst(std::string tagStr) {
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
        int time_in_ms = std::stoi(num);	// currently time in whatever units specified.

	if (units == "ms")
		time_in_ms *= 1000;
	if (units == "s") 		// now convert to milleseconds and return.
		time_in_ms *= 1000000;
	return time_in_ms;
}


void Preset::clear() {
	if (bank != nullptr)
		bank->clear();
}

void Preset::sleep() {
	usleep(presetLoopYield);// wait awhile.
}	


/* async callback - this runs the preset through one interation and then returns.
 * returns false if our time is up
 */
bool Preset::iterate(Preset *p2) {
	Bank *b2 = NULL;	// by default, B2 is null, which means we use our own framebuffer!
        long long expiry_time = timeSinceEpochMillisec() + duration/1000, cur_time = 0;

	cur_time = timeSinceEpochMillisec();

	if (p2 != NULL)
		b2 = p2->bank;
	while(bank->range(b2))   // compute all values for one cycle, whatever that was predetermined to be.
		;               // yes the semicolon is necessary.  Do not delete it!

	bank->dump();          // draw the cycle of waveforms and animation frame, where appropriate.

	if (expiry_time - cur_time > 0)
		return false;

	return true;
}


// this synchronous method runs the preset as quickly as possible in a loop; does not exit until done.
int Preset::run() {
	long long expiry_time = timeSinceEpochMillisec() + duration/1000, cur_time = 0;

	// A N I M A T E   O U R   T R I G   F U N C T I O N S
	////////////////////////////////////////////////////////////
	// run a trigonometric animation cycle for awhile.
	do {
		cur_time = timeSinceEpochMillisec();
//		cout << cur_time << "   " << expiry_time << "\n";


		// this loop executes quickly in some sort of fraction of a second, depending on predetermined cycle+resolution
		while(bank->range(NULL)) 	// compute all values for one cycle, whatever that was predetermined to be.
			;		// yes the semicolon is necessary.  Do not delete it!


		bank->dump();          // draw the cycle of waveforms and animation frame, where appropriate.
		usleep(presetLoopYield);// wait awhile.
		bank->clear();		// clear the bitmap.
		std::system("clear");	// clear the screen.

	}
	while(expiry_time - cur_time > 0);
	return 0;
}
