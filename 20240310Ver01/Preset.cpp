#include <fstream>
#include <iostream>     // std::cout
#include <sstream>      // std::istringstream
#include <string>       // std::string
#include <map>
#include <chrono>	// time functions
#include <unistd.h>	// std::usleep

#include "Preset.h"
#include "Bank.h"

#define TAG_DELAY		"initial_delay"
#define TAG_DURATION		"duration"
#define TAG_FILE		"file"
#define TAG_LOOP_YIELD_DELAY	"loop_yield_time"
#define TAG_OSC1_INC_RATE	"osc1_inc_rate"
#define TAG_OSC2_INC_RATE	"osc2_inc_rate"


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

int Preset::run() {
	uint64_t delay = 		unitsToms( appsets[TAG_DELAY], TAG_DELAY );
	usleep(delay);

	uint64_t duration = 		unitsToms( appsets[TAG_DURATION], TAG_DURATION );
	uint64_t presetLoopYield = 	unitsToms( appsets[TAG_LOOP_YIELD_DELAY], TAG_LOOP_YIELD_DELAY );

//	std::cout << timeSinceEpochMillisec() << std::endl;

	long long expiry_time = timeSinceEpochMillisec() + duration/1000, cur_time = 0;

	float osc1_inc_rate = std::stof(appsets[TAG_OSC1_INC_RATE]);

cout << "expiry time:  " << expiry_time << "\n";

        Oscill osc_ary[] = { Oscill(osc1_inc_rate) };
        int osc_count = sizeof(osc_ary) / sizeof(osc_ary[0]);
        Bank *bank1 = new Bank(osc_ary, osc_count);
        Sprite *sprite = new Sprite(appsets[TAG_FILE], 23);

	do {
		cur_time = timeSinceEpochMillisec();
		cout << cur_time << "   " << expiry_time << "\n";

		bank1->setSprite(sprite);       // attach the animation to the oscillator bank.

		while(bank1->range()) {
			bank1->dump();          // iterate and draw waveforms and animation.
			usleep(presetLoopYield);
			std::system("clear");
			bank1->clear();
        }

	delete sprite;
        delete bank1;

	}
	while(expiry_time - cur_time > 0);

	return 0;
};



