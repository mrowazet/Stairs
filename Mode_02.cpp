#include "Mode_02.h"

Mode_02::Mode_02(int * stepsPtr, const int size)
	:Mode(stepsPtr, size)
{
}

void Mode_02::turnOn()
{
	for (int i = tabSize - 1; i > -1; i--)
	{
		digitalWrite(steps[i], HIGH);
		delay(stepDelay);
	}
}

void Mode_02::turnOff()
{
	for (int i = tabSize -1; i > -1; i--)
	{
		digitalWrite(steps[i], LOW);
		delay(stepDelay);
	}
}

Mode_02::~Mode_02()
{
}
