#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sprite.h"

#include <fstream>
#include <filesystem>
#include <iostream>     // std::cout
#include <sstream>      // std::istringstream
#include <string>       // std::string

using namespace std;



Sprite::Sprite() {
	current = -1;
	size = -1;
}

Sprite::Sprite(std::string filename, int height) {
	std::string line;
	std::ifstream rfile;
	int linecount = 0;
	int firstesc = -1, secondesc = -1;

	size = filesize(filename);
	this->frame_height = 0;
	this->frame_width = 0;

	rfile.open(filename);
	if (rfile.is_open()) {
		while (std::getline(rfile, line)) {

			int pos = line.find(27);	// try to remove the ESCAPE sequences
			if (pos > -1) {			// as we read the file.
				line.erase (pos, 3);
				if (firstesc == -1)	// now try to automagically figure out
					firstesc = linecount;	// the height of the anim frames!
				else
				if (secondesc == -1)
					secondesc = linecount;
			}

			// save maximum column count in any frame to frame_width (used for centering later)
			if (line.length() > this->frame_width)
				this->frame_width = line.length();

			sprite_map += line;
			sprite_map += "\n";
			linecount++;
		}
		rfile.close();
	}
	current = 0;	// by default point at 0th frame in animation.
	this->frame_height = secondesc - firstesc;	// we should have the animation cell height!
	if (this->frame_height < 0)
		this->frame_height = height;
	this->frame_total = linecount / height;
}

std::string Sprite::transmogrify( const std::string &s ) {
    struct Local {
        static std::string indentLine( const std::string &s ) {
            return ">> " + s;
        }
    };

    std::istringstream input( s );
    std::ostringstream output;
    std::transform( std::istream_iterator<std::string>( input ), 
                    std::istream_iterator<std::string>(),
                    std::ostream_iterator<std::string>( output, "\n" ),
                    Local::indentLine );
    return output.str();
}

// get size of file before reading it
std::ifstream::pos_type Sprite::filesize(std::string filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}


std::string Sprite::lineAt(std::string const & in, int frameno) {
	std::istringstream ss(in);
	std::string line;
	int count = 0;
	int escapes_in_line1 = -1;
	int escapes_in_line2 = -1;

	int start_line = this->frame_height * frameno;
	std::string indexed_frame;
	while(getline(ss, line)) {
		if  ( count >= start_line && count < start_line+frame_height) {	
			indexed_frame.append(line);	// we add the a CR to note linebreaks but
			indexed_frame.append("\n");	// later must remove before framebuffer use.
		}
		count++;
	}
	return indexed_frame;
}


Sprite::~Sprite() {
}


std::string Sprite::eval(int frameno) {
	return lineAt(sprite_map, frameno);
}

std::string Sprite::next() {
	string frame = lineAt(sprite_map, current);
	if (++current >= frame_total)
		current = 0;
	return frame;
}


