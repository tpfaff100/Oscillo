#include <fstream>
#include <iostream>     // std::cout
#include <sstream>      // std::istringstream
#include <string>       // std::string
#include <map>
#include <chrono>	// time functions
#include <unistd.h>	// std::usleep

#include "Preset.h"

#define TAG_DELAY	"delay"
#define TAG_DURATION	"duration"
#define TAG_FILE	"file"


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
// and convert to milleseconds because that is what usleep() takes.
// supported units:  (s)econds and (ms) milleseconds
int Preset::unitsToms(string data, string tag) {
        string num = first_number_in_str(appsets[tag]);
        string units = first_units_in_str(appsets[tag]);
        int time_in_ms = std::stoi(num);	// currently time in whatever units specified.
	
	if (units == "ms")			// now convert to milleseconds and return.
		time_in_ms *= 1000;
	if (units == "s")
		time_in_ms *= 1000000;
	return time_in_ms;
}

int Preset::run() {
#if 0
	cout << appsets["delay"] << "\n";
	cout << appsets["file"] << "\n";
	cout << appsets["duration"] << "\n";
#endif

	uint64_t delay = unitsToms( appsets["delay"], TAG_DELAY);
	usleep(delay);
	uint64_t duration = unitsToms( appsets["duration"], TAG_DURATION);

	std::cout << timeSinceEpochMillisec() << std::endl;

	uint64_t expiry_time = timeSinceEpochMillisec() + duration, cur_time = -1;;
cout << cur_time << "   " << expiry_time << "\n";

	do {
		cur_time = timeSinceEpochMillisec();
		usleep(1000000);
		cout << "*\n";
	}
	while(cur_time < expiry_time);


	return 0;
};

