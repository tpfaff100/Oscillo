/** Oscillo - written March 8, 2025, mostly.  This program is designed to replace
 **           my 8-channel quadrature oscillator synthesizer/analog computer thing
 **           I built years ago.  It consisted of a bank of Burr Brown 4423 quadrature
 **           oscillators, a mixer, a frequency multiplier and opamps, etc.
 **            Was lots of fun as an interactive engine and I did many shows
 **            with it in the past but it's time to render the functionality into code
 **
 ** Thomas Poff  March 2025  Just make it should build on Linux, MacOS, Cygwin, etc
 ** Updated in Jun 2026 to implement collection classes to manage the data structures a bit.
 ** Also added "presets" so you can PLAY one or more files instead of writing code.
 **
 ** Requirements:  gcc, g++, make utility.  This module is mostly C code the rest is C++
 */

/** Legend v1:
 **  A "Trig" object defines a sin or cos.  Not entirely efficient these could be done with integer-based lookup tables but currently are floating point 
 **  An "Oscill"ator object defines a quadrature oscillator.  It can generate a sin and cos waveform.
 **  A  "Bank" defines a collection of oscillators.  These can be plotted on top of each other or can be merged (added) together
 **
 **  Typically you want to create a bank of oscillators.  The oscillators are defined in a simple array.
 **  You need to clear the screen after each successive image is drawn.  After clearing screen...
 **  Then call the -->range() method repeatedly on the bank.  This will cycle through all of the oscillators and add them together
 **  Continue until the range exits.  You can also specify new range values 
 **  The bank also creates a "bitmap" which is drawn into and then displayed on the screen.
 **  
 **  pseudocode:  new Bank(oscillators); create phase shift from zero to PI*n.  Clear the bank and call  while(range()) until exit.
 **               Then call dump() to write the created bitmap (with the trig data) on the screen.
 **               adjust phase shift on any oscillators you like and start over (not reallocating anything of course).
 **		  See Test_Bank() for the C code that does all this.
 */

/** Legend for v2:
 **  Use files in presets directory to activate different animation patterns in real time.
 **  
 **  Try these cmds:
 ** ./oscillo -p presets/Anim.prs presets/Animflower.prs presets/Time.prs presets/Anim2.prs
 ** ./oscillo -p presets/Time.prs presets/ColorTest.prs
 ** ./oscillo -p presets/Anim.prs presets/Time.prs
 **
 **  Regression tests can now be run by using the '-t' param:
 ** ./oscillo -t [0-9]
 **
 */

#include <iostream>
#include <string>
#include <vector>

#include <unistd.h>

#include "Regress.h"
#include "Preset.h"

#define ASPECT_X	4
#define ASPECT_Y	3	
#define DELAY		70000




// Given a list of filenames, send the list to a new instance of the Preset object and let it draw them as animations.
// One or more files may be specified.
void process_files(const std::vector<std::string>& filenames) {
	Preset pr(filenames);
}



int main(int argc, char* argv[]) {
	std::vector<std::string> args(argv, argv + argc);
	bool forceMode = false;


	for (size_t i = 1; i < args.size(); ++i) {

		// regression tests
		if (args[i] == "-t") {	// specify that we're running regression test.
			std::string sTestNo = args[++i];
			try {
				int n = std::stoi(sTestNo);
				Regress r;
				r.Test_Regression_Suite(n);
			}
			catch (const std::invalid_argument& e) {
				std::cout << "Try '-t' with a number from 1-9\n\n";
			}
			catch (const std::out_of_range& e) {
				std::cerr << "Out of range: The number is too large for the type.\n";
			}
		}

		// specify file or files to process [maybe look in presets directory]
		// examples: ./oscillo -p presets/Anim.prs presets/Animflower.prs presets/Time.prs presets/Anim2.prs
		//           ./oscillo -p presets/Time.prs presets/ColorTest.prs
		//           ./oscillo -p presets/Anim.prs presets/Time.prs
		else if (args[i] == "-p") {		// check to see if user spec'd PRESET files
		
			++i;
			std::vector<std::string> filenames;
			for (int j = i; j < argc; ++j)
				filenames.push_back(std::string(argv[j]));

			if (filenames.empty()) {
				std::cout << "Usage: " << argv[0] << " <file1> <file2> ... <fileN>\n";
				return 1;
			}
			process_files(filenames);
		}
		// Handle unexpected/unknown flags
		else {
		    std::cerr << "Unknown argument: " << args[i] << "\n";
		    return 1;
		}
	}

	std::cout << "You didn't specify any parameters.  Try running\n./oscillo -p presets/Time.prs presets/Anim2.prs\n./oscillo -t [0-9]\n./oscillo -p presets/Time.prs presets/ColorTest.prs\n\n";
	return 0;
}
