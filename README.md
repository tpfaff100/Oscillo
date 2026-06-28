# Oscillo

Simulator of an analog computer / synthesizer / laser imaging system using trig waveforms and combinations

20260619Ver02 has been released and has the following improvements

Code and functional updates:
- Added Presets to allow loading of files to generate waveforms
- Added options to control timing for displaying complex waveforms
- Added preset files to use with presets:
<br>
  example:
<br>
<br>
              cd ../20260619Ver02
<br>
              make
<br>
              ./oscillo -p presets/[file1.prs] [file2.prs] [file3.prs]
<br>
              ./oscillo -p presets/Anim4.prs
<br>
              ./oscillo -p presets/StarFlower.prs presets/Anim.prs
<br>
<br>
- Supports multiple presets at one time if you want and the timebases are blended.  First oscillator specs the duration to run
- Program now exits when time limit has expired
- Compiles on Linux and MacOS, using C++ Version 20 or better
- Updated to use C++ collection classes to facilitate new extensions and features
- Moved the old test programs into 'regression' suite.  These can be run as follows:
<br>
<br>
              ./oscillo -t [1-9]
<br>
<br>

This allows testing of each improvement and shows backward/historical compatability as the application developed.
These regression tests are also helpful in understanding how the different layers of software operate (simple to complex)

---------------------------------------------------------------
This version features:

Each oscillator controls a sine and cosine waveform.
i.e. each oscillator is a quadrature oscillator.

Each bank contains multiple oscillators.  The intent is to have six but probably more are fine if you need them.
For laser projection, usually two or three are used for a base shape with two high-speed oscillators used to modulate the image.
Beyond that it gets difficult to keep track of what's going on.  For this reason I have in my mind- banks of six oscillators.

Note that this is intended for use with x,y coordinate plane, as was the original laser imaging system.
Can we potentially do more than that?  Yes, of course.

Each PRESET can have a Bank of oscillators.  There is a 1:1 relationship between a 'preset' and a 'bank of oscillators.'
For now I want them in unrelated classes but yes these could be merged into a class hierarchy.  Will see.

Triangle and Sawtooth waveform generation is not completed yet.

I did some testing with cosine lookup tables on Macos.  It seems to me there is not a lot of advantage moving away from the math libraries.
I left an implementation in there for future testing on different platforms but it probably doesn't make sense with math+floating point hardware
so advanced now!  Maybe if you want to run this on a Raspberry PI it might be worth looking at optimizing the sine/cos lookups.

I'm keeping the old Ver01 copy of Oscillo around just because I like looking at it once in awhile.  Maybe will delete it someday.

---------------------------------------------------------------
Original release 20240310Ver01 - (old version)

Simulator of an analog computer / synthesizer / laser imaging system using trig waveforms and combinations

I have spent a few weekends on this project it currently supports a group of quadrature oscillators, rendering output
into a virtual framebuffer that (for ease of implementation) consists of text in the unix command line.  I'm in the
process of modifying it to allow preset files to create a timed sequence of events to render.

There are two functions in main() one of them is procedural and the other is object-based.

The idea is to have two banks of x-y oscillators one that lets you switch out basic shapes, mixing those together and
another bank of oscillators for high-frequency modulation (used for making shapes modulate or "warble" using
scalar frequency multiples (ok harmonics I suppose) at much faster rates.  This always made for great laser shows
that I did in the old days.

There are pluses and minuses to having a computer do all this since a lot of the fun was in the sponanaeity w/ regard
to having imperfect potentiometers.  You had to _play_ the laser imager as an instrument whereas the digital versions
have always been dull as mud, as they lack imperfection, etc.

Will see if with this model I can improve on that.

Right now when you run it you will see shapes animating in your terminal shell.  Pretty fun!

Why did I do this?

1.  I find modern UI models unrefined (I know... how arrogant huh?!)
    I mean javascript is nice coz it runs everywhere but it runs in -mostly- a single thread
      and is fairly slow.  Other UI models aren't shared easily so I thought well...
2.  I could just use terminal and make the characters really small and do whatever animations
      I want a custom character depths!  Works pretty well...
3.  And it should run everywhere.  Even under Termux (similar to Ubuntu) on my Android!

Sample build+output when run:
(two quadrature oscillators added together, slightly out of phase with each other)
![Oscillo screen shot](https://github.com/tpfaff100/Oscillo/blob/main/triganime.gif?raw=true)
![Oscillo screen shot](https://github.com/tpfaff100/Oscillo/blob/main/triganime2.gif?raw=true)

The original Laser Imaging System Head/Computer I'm emulating looks like this:

![Laser Imaging System 1](https://github.com/tpfaff100/Oscillo/blob/main/AnalogLaserImagingSynth02.jpg?raw=true)
![Laser Imaging System 1](https://github.com/tpfaff100/Oscillo/blob/main/AnalogLaserImagingSynth01.jpg?raw=true)
