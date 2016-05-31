#include "Lights.h"
#include "Mode.h"
#include "Mode_01.h"
#include "Mode_02.h"

Lights::Lights(const int nrSteps, const int firstPin)
	:nrOfSteps(nrSteps)
{
	init(firstPin);
	enabler = new Mode_01(steps, nrOfSteps);
	disabler = new Mode_01(steps, nrOfSteps);
}

Lights::~Lights()
{
	delete[] steps;

	if (enabler)
		delete enabler;

	if (disabler)
		delete disabler;
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

void Lights::turnOnLights()
{
	enabler->turnOn();
}

void Lights::turnOffLights()
{
	disabler->turnOff();
}

void Lights::setEnablerDelay(const int wantedDelay)
{
	enabler->setDelay(wantedDelay);
}

void Lights::setDisablerDelay(const int wantedDelay)
{
	disabler->setDelay(wantedDelay);
}
