// Indicator.h

#ifndef _INDICATOR_h
#define _INDICATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Indicator
{
public:
	Indicator(const int & pinNr);
	~Indicator();
	void on();
	void off();

private:
	const int Pin;
};

#endif

