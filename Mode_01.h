// Mode_01.h

#ifndef _MODE_01_h
#define _MODE_01_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Mode.h"

class Mode_01 : public Mode
{
	public:
		Mode_01(int * stepsPtr, const int size);
		virtual void turnOn();
		virtual void turnOff();
		virtual void clearStepNr();
		virtual ~Mode_01();
};

#endif

