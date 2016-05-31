// Lights.h

#ifndef _LIGHTS_h
#define _LIGHTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Mode;

class Lights
{
public:
	Lights(const int nrSteps, const int firstPin);
	~Lights();

	void turnOnLights();
	void turnOffLights();

	void changeEnabler();
	void changeDisabler();

	void setEnablerDelay(const int wantedDelay);
	void setDisablerDelay(const int wantedDelay);

private:
	const int nrOfSteps;
	int * steps;
	Mode * enabler = nullptr;
	Mode * disabler = nullptr;

	void init(const int firstPin);
};

#endif

