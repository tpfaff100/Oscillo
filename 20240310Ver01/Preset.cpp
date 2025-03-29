#include <fstream>
#include <iostream>     // std::cout
#include <string>       // std::string
#include <map>
#include <unistd.h>	// std::usleep

#include "Preset.h"

#define TAG_DELAY	"delay"
#define TAG_DURATION	"duration"
#define TAG_FILE	"file"


using namespace std;



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

int Preset::run() {
#if 0
	cout << appsets["delay"] << "\n";
	cout << appsets["file"] << "\n";
	cout << appsets["duration"] << "\n";
#endif

	string num = first_number_in_str(appsets[TAG_DELAY]);
	string units = first_units_in_str(appsets[TAG_DELAY]);
	int delay = std::stoi(num);

	if (units == "ms")
		delay *= 1000;
	if (units == "s")
		delay *= 1000000;

	usleep(delay);

	num = first_number_in_str(appsets[TAG_DURATION]);
	units = first_units_in_str(appsets[TAG_DURATION]);
	int duration = std::stoi(num);

	if (units == "ms")
		duration *= 1000;
	if (units == "s")
		duration *= 1000000;

//	usleep(duration);


	return -1;
};

