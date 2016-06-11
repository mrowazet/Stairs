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
	void resetDisablersCounters();

	bool isIlluminated();
	bool isAnyLightEnabled();

	void changeEnablerDown(const int & modeNr);
	void changeEnablerUp(const int & modeNr);
	void changeDisablerDown(const int & modeNr);
	void changeDisablerUp(const int & modeNr);

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

	Mode * getMode(const int & mode);

	void init(const int firstPin);
};

#endif

