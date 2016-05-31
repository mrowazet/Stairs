// Mode_03.h

#ifndef _MODE_03_h
#define _MODE_03_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Mode.h"

class Mode_03 : public Mode
{
public:
	Mode_03(int * stepsPtr, const int size);
	virtual void turnOn();
	virtual void turnOff();
	virtual void clearStepNr();
	virtual ~Mode_03();
};

#endif

