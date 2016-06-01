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
	Lights(const int & nrSteps, const int & firstPin);
	~Lights();

	void turnOnLightsDown();
	void turnOnLightsUp();
	void turnOffLightsDown();
	void turnOffLightsUp();
	void turnOnLightsImmediately();
	void turnOffLightsImmediately();

	void resetEnablersCounters();

	bool isIlluminated();

	void changeEnablerDown();
	void changeEnablerUp();
	void changeDisablerDown();
	void changeDisablerUp();

	void setEnablerDelay(const int wantedDelay);
	void setDisablerDelay(const int wantedDelay);

private:
	const int nrOfSteps;
	int * steps;
	Mode * enablerDown = nullptr;
	Mode * disablerDown = nullptr;
	Mode * enablerUp = nullptr;
	Mode * disablerUp = nullptr;
	Mode * immediatelySwitch = nullptr;

	void init(const int firstPin);
};

#endif

