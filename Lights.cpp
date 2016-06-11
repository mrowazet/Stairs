#include "Lights.h"
#include "Mode.h"
#include "Mode_01.h"
#include "Mode_02.h"
#include "Mode_03.h"

Lights::Lights(const int & nrSteps, const int & firstPin)
	:nrOfSteps(nrSteps)
{
	init(firstPin);
	enablerDown = new Mode_01(steps, nrOfSteps);	//default 01
	disablerDown = new Mode_01(steps, nrOfSteps);	//default 01	
	enablerUp = new Mode_02(steps, nrOfSteps);		//default 02
	disablerUp = new Mode_02(steps, nrOfSteps);		//default 02

	immediatelySwitch = new Mode_03(steps, nrOfSteps);	//default 03
}

Lights::~Lights()
{
	delete[] steps;

	if (enablerDown) delete enablerDown;
	if (disablerDown) delete disablerDown;
	if (enablerUp) delete enablerUp;
	if (disablerUp) delete disablerUp;
}

void Lights::turnOnLightsDown()
{
	enablerDown->turnOn();
}

void Lights::turnOnLightsUp()
{
	enablerUp->turnOn();
}

void Lights::turnOffLightsDown()
{
	disablerDown->turnOff();
}

void Lights::turnOffLightsUp()
{
	disablerUp->turnOff();
}

void Lights::init(const int firstPin)
{
	int pin = firstPin;
	steps = new int[nrOfSteps];
	for (int i = 0; i < nrOfSteps; i++)
	{
		steps[i] = pin;
		pinMode(steps[i], OUTPUT);
		pin++;
	}

}

bool Lights::isIlluminated()
{
	for (int i = 0; i < nrOfSteps; i++)
	{
		if (digitalRead(steps[i]) == LOW)
			return false;
	}

	return true;
}

bool Lights::isAnyLightEnabled()
{
	for (int i = 0; i < nrOfSteps; i++)
	{
		if (digitalRead(steps[i]) == HIGH)
			return false;
	}

	return true;
}

void Lights::changeEnablerDown(const int & modeNr)
{
	Mode * tmp = enablerDown;
	enablerDown = getMode(modeNr);
	delete tmp;
}

void Lights::changeEnablerUp(const int & modeNr)
{
	Mode * tmp = enablerUp;
	enablerUp = getMode(modeNr);
	delete tmp;
}

void Lights::changeDisablerDown(const int & modeNr)
{
	Mode * tmp = disablerDown;
	disablerDown = getMode(modeNr);
	delete tmp;
}

void Lights::changeDisablerUp(const int & modeNr)
{
	Mode * tmp = disablerUp;
	disablerUp = getMode(modeNr);
	delete tmp;
}

Mode * Lights::getMode(const int & mode)
{
	switch (mode)
	{
		case 1:
			return new Mode_01(steps, nrOfSteps);
		break;

		case 2:
			return new Mode_02(steps, nrOfSteps);
		break;

		case 3:
			return new Mode_03(steps, nrOfSteps);
		break;
	}
}

void Lights::setEnablerDelay(const int wantedDelay)
{
	enablerDown->setDelay(wantedDelay);
	enablerUp->setDelay(wantedDelay);
}

void Lights::setDisablerDelay(const int wantedDelay)
{
	disablerDown->setDelay(wantedDelay);
	disablerUp->setDelay(wantedDelay);
}

void Lights::turnOnLightsImmediately()
{
	immediatelySwitch->turnOn();
}

void Lights::turnOffLightsImmediately()
{
	immediatelySwitch->turnOff();
}

void Lights::resetEnablersCounters()
{
	enablerDown->clearStepNr();
	enablerUp->clearStepNr();
}

void Lights::resetDisablersCounters()
{
	disablerDown->clearStepNr();
	disablerUp->clearStepNr();
}
