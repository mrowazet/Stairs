// DefaultOptionsParams.h

#ifndef _DEFAULTOPTIONSPARAMS_h
#define _DEFAULTOPTIONSPARAMS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class DefaultOptionsParams
{
	public:
		const int TurnOnMode_Down = 1;				//tryb
		const int TurnOnMode_Up = 2;				//tryb
		const int TurnOnStepDelay = 200;			//delay przy wlaczaniu
		const int TurnOffMode_Down = 1;				//tryb
		const int TurnOffMode_Up = 2;				//tryb
		const int TurnOffStepDelay = 200;			//delay przy wylaczaniu
		const int LitTime = 3000;					//czas swiecenia po pelnym zapaleniu
		const int MinDelaySwitchStep = 50;			//min wartosc dla step delay
		const int MaxDelaySwitchStep = 500;			//max wartosc dla step delay
		const int StepSwitch = 50;					//krok dla zmiany step delay
		const int MinLitTime = 2000;				//min cza swiecenia	
		const int MaxLitTime = 10000;				//max czas swiecenia
		const int StepLitTime = 1000;				//ktok dla zmiany lit time
		const int StepMode = 1;						//krok dla zmiany trybu
};

#endif

