#include "Mode_01.h"

Mode_01::Mode_01(int * stepsPtr, const int size)
	:Mode(stepsPtr, size)
{
}

void Mode_01::turnOn()
{
	for (int i = 0; i < tabSize; i++)
	{
		digitalWrite(steps[i], HIGH);
		delay(stepDelay);
	}
}

void Mode_01::turnOff()
{
	for (int i = 0; i < tabSize; i++)
	{
		digitalWrite(steps[i], LOW);
		delay(stepDelay);
	}
}

Mode_01::~Mode_01()
{
}
