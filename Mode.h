// Mode.h

#ifndef _MODE_h
#define _MODE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Mode
{
	public:
		Mode(int * stepsPtr, const int size);
		void setDelay(int ms);
		int getDelay();
		virtual void turnOn() = 0;
		virtual void turnOff() = 0;
		virtual void clearStepNr() = 0;
		virtual ~Mode();

	protected:
		const int tabSize;
		int * steps;
		int stepDelay = 300;
		int stepNr = 0;
};

#endif

