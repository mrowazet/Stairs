// StatusLed.h

#ifndef _STATUSLED_h
#define _STATUSLED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class StatusLed
{
public:
	StatusLed(const int & pinNr);
	~StatusLed();
	void on();
	void off();

private:
	const int Pin;
};

#endif

