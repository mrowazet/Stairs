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

	void turnOnLights(bool isDownSensor);
	void turnOffLights(bool isDownSensor);
	void turnOffLightsImmediately();
	void resetEnablersCounters();

	bool isIlluminated();

	void changeEnabler();
	void changeDisabler();

	void setEnablerDelay(const int wantedDelay);
	void setDisablerDelay(const int wantedDelay);

private:
	const int nrOfSteps;
	int * steps;
	Mode * enablerDown = nullptr;
	Mode * disablerDown = nullptr;
	Mode * enablerUp = nullptr;
	Mode * disablerUp = nullptr;
	Mode * immediatelyDisabler = nullptr;

	void init(const int firstPin);
};

#endif

