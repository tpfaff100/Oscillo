#ifndef PRESET_H
#define PRESET_H

#include <map>
#include <string>


class Preset
{
	std::map<std::string, std::string> appsets;

	int unitsToms(std::string data, std::string tag);

public:
	Preset(std::string file);
	int run(void);
};

#endif
