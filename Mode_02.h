// Mode_02.h

#ifndef _MODE_02_h
#define _MODE_02_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Mode.h"

class Mode_02 : public Mode
{
public:
	Mode_02(int * stepsPtr, const int size);
	virtual void turnOn();
	virtual void turnOff();
	virtual ~Mode_02();
};

#endif

