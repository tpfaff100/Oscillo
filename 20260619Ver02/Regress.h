#ifndef REGRESS_H
#define REGRESS_H




enum { None,
        Test_1_Waveform_Anim,
        Test_2_Oscillator_One,
        Test_3_Oscillators_Multi,
        Test_4_Bank_of_Oscillators,
        Test_5_Invert_Axes,
        Test_6_Colors,
        Test_7_Sprite,
        Test_8_Preset,
        Test_9_Presets_Multi,
};

class Regress
{
public:
	void Test_Regression_Suite(int n);


	void Test_Presets(); 
	void Test_Preset(); 
	void Test_Color();
        void Test_Sprite();
	void Test_Invert_Axes(); 
	void Test_Bank();
	void Test_Oscillators(); 
	void Test_Oscillator(); 
	void Test_Waveform_Anim(); 
};

#endif

