#ifndef SPRITE_H
#define SPRITE_H

#define MAX_SPRITE_LEN	65535

#include <filesystem>
#include <fstream>
#include <string>
#include "Types.h"

class Sprite 
{
        std::string sprite_map; // string containing the entire animation (all frames)
	int frame_height;	// number of lines in each frame.
	int frame_total;	// total number of frames in animation.
	int size;		// number of bytes in the shape.
	int current;		// specify the current frame # in the sprite animation.

public:
	Sprite();
	Sprite(std::string filename, int height);
	~Sprite();
	std::string eval(int);
	std::string next(void);

	std::string lineAt(std::string const & in, int index); 
	std::ifstream::pos_type   	filesize(std::string filename);
	std::string  			transmogrify( const std::string &s ); 

};

#endif
