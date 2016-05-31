#include "Mode_03.h"

Mode_03::Mode_03(int * stepsPtr, const int size)
	:Mode(stepsPtr, size)
{
}

void Mode_03::turnOn()
{
	for (int i = 0; i < tabSize; i++)
		digitalWrite(steps[i], HIGH);
}

void Mode_03::turnOff()
{
	for (int i = 0; i < tabSize; i++)
		digitalWrite(steps[i], LOW);
}

void Mode_03::clearStepNr()
{
	stepNr = 0;
}

Mode_03::~Mode_03()
{
}
