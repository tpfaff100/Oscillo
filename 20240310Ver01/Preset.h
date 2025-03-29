#ifndef PRESET_H
#define PRESET_H

#include <map>
#include <string>


class Preset
{
	std::map<std::string, std::string> appsets;
public:
	Preset(std::string file);
	int run(void);
};

#endif
