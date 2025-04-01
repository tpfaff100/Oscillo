# Oscillo
Simulator of an analog computer / synthesizer / laser imaging system using trig waveforms and combinations thereof

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

The original Laser Imaging System Head/Computer I'm emulating looks like this:

![Laser Imaging System 1](https://github.com/tpfaff100/Oscillo/blob/main/AnalogLaserImagingSynth02.jpg?raw=true)
![Laser Imaging System 1](https://github.com/tpfaff100/Oscillo/blob/main/AnalogLaserImagingSynth01.jpg?raw=true)
